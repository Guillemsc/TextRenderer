#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <math.h> 
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <assert.h>
#include <functional>

#define TEXT_RENDERER_VERSION "0.01"

// ---------------------------------------------------------------------------------------------------------
// STB Truetype --------------------------------------------------------------------------------------------

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"

// ---------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------
// Defines -------------------------------------------------------------------------------------------------

#define TR_DEL( x )		\
    {                       \
    if( x != nullptr )      \
	    {                   \
      delete x;             \
	  x = nullptr;          \
	    }                   \
    }

#define TR_DEL_ARRAY( x )  \
    {                       \
    if( x != nullptr )      \
	    {                   \
      delete[] x;           \
	  x = nullptr;          \
	    }                   \
                            \
    }

#define DEGTORAD   0.0174532925199432957f
#define RADTODEG   57.295779513082320876f
#define PI		   3.14159265358979323846f
#define TWO_PI	   6.28318530717958647692f
#define HALF_PI	   1.57079632679489661923f
#define QUARTER_PI 0.78539816339744830961f
#define INV_PI	   0.31830988618379067154f
#define INV_TWO_PI 0.15915494309189533576f

#define TR_ASSERT(_EXPR, _MSG) assert(_EXPR && _MSG)

// ---------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------
// Typedefs ------------------------------------------------------------------------------------------------

typedef unsigned int TR_uint;
typedef unsigned char TR_uchar;

// ---------------------------------------------------------------------------------------------------------

static TRInternal::TRMain* main = nullptr;

// ---------------------------------------------------------------------------------------------------------
// Custom general use classes ------------------------------------------------------------------------------

class TRVec2
{
public:
	TRVec2();
	TRVec2(float x, float y);

	TRVec2 operator + (const TRVec2& vec);
	TRVec2 operator - (const TRVec2& vec);
	TRVec2 operator * (const TRVec2& vec);
	TRVec2 operator * (int vec);
	TRVec2 operator * (float vec);
	TRVec2 operator / (const TRVec2& vec);
	void operator += (const TRVec2& vec);
	void operator -= (const TRVec2& vec);
	void operator *= (const TRVec2& vec);
	void operator /= (const TRVec2& vec);

	float Distance(const TRVec2& vec);

public:
	float x = 0.0f;
	float y = 0.0f;
};

class TRVec3
{
public:
	TRVec3();
	TRVec3(float x, float y, float z);

	TRVec3 operator + (const TRVec3& vec);
	TRVec3 operator - (const TRVec3& vec);
	void operator += (const TRVec3& vec);
	void operator -= (const TRVec3& vec);
	void operator *= (const TRVec3& vec);
	void operator /= (const TRVec3& vec);

	float Distance(const TRVec3& vec);

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

class TRVec4
{
public:
	TRVec4();
	TRVec4(float x, float y, float w, float z);

	TRVec4 operator + (const TRVec4& vec);
	TRVec4 operator - (const TRVec4& vec);
	void operator += (const TRVec4& vec);
	void operator -= (const TRVec4& vec);
	void operator *= (const TRVec4& vec);
	void operator /= (const TRVec4& vec);

public:
	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float z = 0.0f;
};

class TRColour
{
public:
	TRColour();
	TRColour(float r, float g, float b);
	TRColour(const TRVec4& vec);
	TRColour(float r, float g, float b, float a);
	TRColour(int hexadecimal_val);

	TRColour operator + (const TRColour& vec);
	TRColour operator - (const TRColour& vec);
	void operator += (const TRColour& vec);
	void operator -= (const TRColour& vec);
	void operator *= (const TRColour& vec);
	void operator /= (const TRColour& vec);

public:
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
};

class TRRect
{
public:
	TRRect();
	TRRect(float x, float y, float w, float h);
	TRRect(const TRVec4& vec);
	TRRect(const TRVec2& pos, const TRVec2 size);

	void operator = (const TRRect& rect);

	inline float xw();
	inline float yh();

	TRVec2 Pos();
	TRVec2 Size();
	TRVec2 Center();

	bool Overlaps(TRRect rec);
	bool Contains(TRRect rec);
	bool Contains(TRVec2 point);
	void Scissor(TRRect rec);

public:
	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float h = 0.0f;
};

class TRBuffer
{
public:
	TRBuffer();
	TRBuffer(int size);
	TRBuffer(int width, int heigth);
	
	void SetSize(int size);
	void SetSize(int width, int heigth);
	void Reset();
	void Clear();

	void AddData(int data_ptr_pos, TR_uchar * data);

	TR_uchar* GetBufferData();
	bool BufferHasData() const;

	int GetWidth();
	int GetHeight();
	int GetSize();

	void FlipUpsideDown();

private:
	TR_uchar * buffer = nullptr;

	int width = 0;
	int heigth = 0;
	int size = 0;
};

template<class TYPE>
class TRVector
{
public:
	TRVector() { };
	TRVector(const TRVector& element) { Substitute(element); };
	~TRVector() { FreeData(); };

	TYPE& operator[] (TR_uint index) { TR_ASSERT(index < data_capacity, "Index out of boundaries"); return data_array[index]; };
	void operator = (const TRVector & element) { Substitute(element); };
	void operator += (const TRVector& element) { Concatenate(element); };

	inline void PushBack(TYPE element)
	{
		if (data_capacity < data_used + 1)
			Resize(data_capacity + chunk_size);

		data_array[data_used++] = element;
	};

	inline void RemoveAt(int index)
	{
		TR_ASSERT(index < data_capacity, "Index out of boundaries");

		for (int i = index; i < data_used - 1; ++i)
			data_array[i] = data_array[i + 1];

		if (data_used > 0)
			--data_used;

		if (data_capacity > data_used + chunk_size)
			Resize(data_capacity - chunk_size);
	};

	inline void Clear() { data_used = 0; };
	inline int Size() { return data_used; };
	inline TYPE* Data() { return data_array; };

private:
	void Resize(TR_uint size)
	{
		if (size > 0 && size > data_used)
		{
			if (data_capacity > 0)
			{
				TYPE* new_data = nullptr;
				new_data = new TYPE[size];

				for (int i = 0; i < data_used; ++i)
					new_data[i] = data_array[i];

				data_capacity = size;

				TR_DEL_ARRAY(data_array);

				data_array = new_data;
			}
			else
			{
				data_array = new TYPE[size];
				data_capacity = size;
			}
		}
	};

	void Substitute(const TRVector& element)
	{
		Clear();
		Resize(element.data_used + chunk_size);

		for (int i = 0; i < element.data_used; ++i)
			data_array[i] = element.data_array[i];

		data_used = element.data_used;
	};

	void Concatenate(const TRVector& element)
	{
		int new_size = data_used + element.data_used;

		if (new_size > data_capacity)
			Resize(new_size);

		for (int i = 0; i < element.data_used; ++i)
			data_array[i] = element.data_array[i];

		data_used = new_size;
	};

	void FreeData(){ TR_DEL_ARRAY(data_array); data_capacity = 0; data_used = 0; }

private:
	TYPE *    data_array = nullptr;
	TR_uint     data_capacity = 0;

	TR_uint     data_used = 0;

	const int chunk_size = 50;
};

template<class TYPE>
class TRVectorMem
{
public:
	TRVectorMem() { };
	TRVectorMem(const TRVectorMem& element) { Substitute(element); };
	~TRVectorMem() { FreeData(); };

	TYPE& operator[] (TR_uint index) { TR_ASSERT(index < data_capacity, "Index out of boundaries"); return data_array[index]; };
	void operator = (const TRVectorMem & element) { Substitute(element); };
	void operator += (const TRVectorMem& element) { Concatenate(element); };

	inline void PushBack(TYPE element)
	{
		if (data_capacity < data_used + 1)
			Resize(data_capacity + chunk_size);

		data_array[data_used++] = element;
	};

	inline void RemoveAt(int index)
	{
		TR_ASSERT(index < data_capacity, "Index out of boundaries");

		for (int i = index; i < data_used - 1; ++i)
			data_array[i] = data_array[i + 1];

		if (data_used > 0)
			--data_used;

		if (data_capacity > data_used + chunk_size)
			Resize(data_capacity - chunk_size);
	};

	inline void Clear() { data_used = 0; };
	inline int Size() { return data_used; };
	inline TYPE* Data() { return data_array; };

private:
	void Resize(TR_uint size)
	{
		if (size > 0 && size > data_used)
		{
			if (data_capacity > 0)
			{
				TYPE* new_data = nullptr;
				new_data = new TYPE[size];

				for (int i = 0; i < data_used; ++i)
					new_data[i] = data_array[i];

				data_capacity = size;

				TR_DEL_ARRAY(data_array);

				data_array = new_data;
			}
			else
			{
				data_array = new TYPE[size];
				data_capacity = size;
			}
		}
	};

	void Substitute(const TRVectorMem& element)
	{
		Clear();
		Resize(element.data_used + chunk_size);

		memcpy(data_array, element.data_array, element.data_used);

		data_used = element.data_used;
	};

	void Concatenate(const TRVectorMem& element)
	{
		int new_size = data_used + element.data_used;

		if (new_size > data_capacity)
			Resize(new_size);

		memcpy(data_array, element.data_array, element.data_used);

		data_used = new_size;
	};

	void FreeData() { TR_DEL_ARRAY(data_array); data_capacity = 0; data_used = 0; }

private:
	TYPE * data_array = nullptr;
	TR_uint     data_capacity = 0;

	TR_uint     data_used = 0;

	const int chunk_size = 50;
};

// ---------------------------------------------------------------------------------------------------------

namespace TRInternal
{
	// -----------------------------------------------------------------------------------------------------
	// Forward declarations --------------------------------------------------------------------------------

	class TRFonts;
	class TRFont;
	class FastGlyph;

	class TRDraw;
	class TRDrawShape;

	// -----------------------------------------------------------------------------------------------------
	// Internal classes ------------------------------------------------------------------------------------

	// ----------------------------------------------------------------------------

	class TRMain
	{
	public:
		TRMain() {};

	public:
		void Init();
		void Quit();

		TRFonts* Fonts();
		TRDraw* Draw();

		void SetViewport(const TRVec4& viewport);
		TRVec4 GetViewport() const;

	private:
		TRVec4 viewport;

		TRFonts* fonts = nullptr;
		TRDraw*  draw = nullptr;
	};

	//-----------------------------------------------------------------------------
	// Fonts
	//-----------------------------------------------------------------------------

	class TRFont
	{
	public:
		TRFont(stbtt_fontinfo font_info);
		~TRFont();

		void CleanUp();

		void SetFontScale(float set);
		float GetFontScale();

		FastGlyph GetGlyphByChar(TR_uchar c);

	public:
		TR_uchar*  texture_data = nullptr;
		TR_uint    texture_id = 0;
		TRVec2 size = TRVec2(0, 0);

		TRVector<FastGlyph> glyphs;

	private:
	

	private:
		stbtt_fontinfo info;
		float		   scale = 0.0f;
	};

	class FastGlyph
	{
	public:
		FastGlyph();

		TRVec2 uvs_x0;
		TRVec2 uvs_y0;
		TRVec2 uvs_x1;
		TRVec2 uvs_y1;

		float    ratio_x_y = 0.0f;
	};

	enum TRFontRange
	{
		FAST_FONT_RANGE_LATIN,
		FAST_FONT_RANGE_KOREAN,
		FAST_FONT_RANGE_CHINESE,
		FAST_FONT_RANGE_JAPANESE,
		FAST_FONT_RANGE_CYRILLIC,
		FAST_FONT_RANGE_THAI,
	};

	class TRFonts 
	{
	public:
		TRFonts();
		~TRFonts();

		void Start();
		void CleanUp();

		void LoadFont(const char* path, int font_size, TRFontRange range = TRFontRange::FAST_FONT_RANGE_LATIN);

		TRFont* GetCurrFont() const;

	private:
		TRVec2 TexturePosToUV(TRVec2 texture_size, TRVec2 pos);

		std::vector<TRVec2> GetBaseGlyphsRanges();
		std::vector<TRVec2> GetLatinGlyphsRanges();
		std::vector<TRVec2> GetKoreanGlyphsRanges();
		std::vector<TRVec2> GetChineseGlyphsRanges();
		std::vector<TRVec2> GetJapaneseGlyphsRanges();
		std::vector<TRVec2> GetCyrillicGlyphsRanges();
		std::vector<TRVec2> GetThaiGlyphsRanges();

	private:
		TRFont* curr_font = nullptr;
	};

	// ----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// Draw
	//-----------------------------------------------------------------------------

	class TRDrawShape
	{
	public:
		TRDrawShape();

		void AddPoint(TRVec2 point_pos);
		void AddTextureId(TR_uint id);
		void Finish(TRColour colour);
		void Finish(TRColour colour, TRVec4 range_uvs);
		void Clear();
		void SetClippingRect(const TRRect& rect);

		TR_uint* GetIndicesPtr();
		TRVector<TR_uint> GetIndices();
		TR_uint GetIndicesCount();
		float* GetVerticesPtr();
		TRVector<float> GetVertices();
		float* GetColoursPtr();
		TRVector<float> GetColours();
		float* GetUvsPtr();
		TRVector<float> GetUvs();
		float* GetVerticesColourUvsPtr();
		TRVector<float> GetVerticesColoursUvs();

		bool GetUsesClippingRect() const;
		TRRect GetClippingRect() const;

		TR_uint GetTextureId();

		TR_uint Offset();
		TR_uint VerticesOffset() const;
		TR_uint VerticesSize() const;
		TR_uint ColourOffset() const;
		TR_uint ColoursSize() const;
		TR_uint UvsOffset() const;
		TR_uint UvsSize() const;

	private:
		TRVector<TR_uint>   indices;
		TRVector<float>     vertices;
		TRVector<float>     colours;
		TRVector<float>     uvs;
		TRVector<float>     vertices_colour_uvs;

		TR_uint				curr_indices_count = 0;

		TR_uint             texture_id = 0;

		bool			    finished = false;
		TRVector<TRVec2>    points;

		bool				uses_clipping_rect = false;
		TRRect			    clipping_rect;

		TRVec4			    quad_size;
	};

	enum TRDrawTextAlign
	{
		FAST_DRAW_TEXT_ALIGN_LEFT,
		FAST_DRAW_TEXT_ALIGN_CENTER,
		FAST_DRAW_TEXT_ALIGN_RIGHT,
	};

	struct TRDrawTextLineInfo
	{
		float x_size = 0;
		TR_uint max_word = 0;
	};

	class TRDraw 
	{
	public:
		 TRDraw();
		~TRDraw();

		void Start();
		void CleanUp();

		TRVector<TRDrawShape>& GetDebugShapes();

		void FontAtlas(TRVec2 pos, TRVec2 size, TRFont* font, TRColour colour);
		void Text(TRVec2 pos, float size, TRFont* font, std::string text, TRColour colour);

	private:
		TRVector<TRDrawShape> debug_shapes;

		bool	    drawing_shape = false;
		TRDrawShape curr_shape;

		bool	    clipping_enabled = false;
		TRRect      curr_clipping_rect;
	};

	// ----------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------------------
}

namespace TR
{
	// -----------------------------------------------------------------------------------------------------
	// User exposed functions ------------------------------------------------------------------------------

	void Init();

	const char* GetVersion();

	void LoadFont(const char* filepath);

	// -----------------------------------------------------------------------------------------------------
}


#endif // !_TEXT_RENDERER
