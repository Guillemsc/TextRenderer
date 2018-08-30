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
#define HAVE_M_PI

#define TR_ASSERT(_EXPR, _MSG) assert(_EXPR && _MSG)

// ---------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------
// Typedefs ------------------------------------------------------------------------------------------------

typedef unsigned int TR_uint;
typedef unsigned char TR_uchar;

// ---------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------
// Custom general use classes ------------------------------------------------------------------------------

class FastVec2
{
public:
	FastVec2();
	FastVec2(float x, float y);

	FastVec2 operator + (const FastVec2& vec);
	FastVec2 operator - (const FastVec2& vec);
	FastVec2 operator * (const FastVec2& vec);
	FastVec2 operator * (int vec);
	FastVec2 operator * (float vec);
	FastVec2 operator / (const FastVec2& vec);
	void operator += (const FastVec2& vec);
	void operator -= (const FastVec2& vec);
	void operator *= (const FastVec2& vec);
	void operator /= (const FastVec2& vec);

	float Distance(const FastVec2& vec);

public:
	float x = 0.0f;
	float y = 0.0f;
};

class FastVec3
{
public:
	FastVec3();
	FastVec3(float x, float y, float z);

	FastVec3 operator + (const FastVec3& vec);
	FastVec3 operator - (const FastVec3& vec);
	void operator += (const FastVec3& vec);
	void operator -= (const FastVec3& vec);
	void operator *= (const FastVec3& vec);
	void operator /= (const FastVec3& vec);

	float Distance(const FastVec3& vec);

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

class FastVec4
{
public:
	FastVec4();
	FastVec4(float x, float y, float w, float z);

	FastVec4 operator + (const FastVec4& vec);
	FastVec4 operator - (const FastVec4& vec);
	void operator += (const FastVec4& vec);
	void operator -= (const FastVec4& vec);
	void operator *= (const FastVec4& vec);
	void operator /= (const FastVec4& vec);

public:
	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float z = 0.0f;
};

class FastColour
{
public:
	FastColour();
	FastColour(float r, float g, float b);
	FastColour(const FastVec4& vec);
	FastColour(float r, float g, float b, float a);
	FastColour(int hexadecimal_val);

	FastColour operator + (const FastColour& vec);
	FastColour operator - (const FastColour& vec);
	void operator += (const FastColour& vec);
	void operator -= (const FastColour& vec);
	void operator *= (const FastColour& vec);
	void operator /= (const FastColour& vec);

public:
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
};

class FastRect
{
public:
	FastRect();
	FastRect(float x, float y, float w, float h);
	FastRect(const FastVec4& vec);
	FastRect(const FastVec2& pos, const FastVec2 size);

	void operator = (const FastRect& rect);

	inline float xw();
	inline float yh();

	FastVec2 Pos();
	FastVec2 Size();
	FastVec2 Center();

	bool Overlaps(FastRect rec);
	bool Contains(FastRect rec);
	bool Contains(FastVec2 point);
	void Scissor(FastRect rec);

public:
	float x = 0.0f;
	float y = 0.0f;
	float w = 0.0f;
	float h = 0.0f;
};

class FastBuffer
{
public:
	FastBuffer();
	FastBuffer(int size);
	FastBuffer(int width, int heigth);
	
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
class FastVector
{
public:
	FastVector() { };
	FastVector(const FastVector& element) { Substitute(element); };
	~FastVector() { FreeData(); };

	TYPE& operator[] (Fuint index) { FAST_ASSERT(index < data_capacity, "Index out of boundaries"); return data_array[index]; };
	void operator = (const FastVector & element) { Substitute(element); };
	void operator += (const FastVector& element) { Concatenate(element); };

	inline void PushBack(TYPE element)
	{
		if (data_capacity < data_used + 1)
			Resize(data_capacity + chunk_size);

		data_array[data_used++] = element;
	};

	inline void RemoveAt(int index)
	{
		FAST_ASSERT(index < data_capacity, "Index out of boundaries");

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
	void Resize(Fuint size)
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

				FAST_DEL_ARRAY(data_array);

				data_array = new_data;
			}
			else
			{
				data_array = new TYPE[size];
				data_capacity = size;
			}
		}
	};

	void Substitute(const FastVector& element)
	{
		Clear();
		Resize(element.data_used + chunk_size);

		for (int i = 0; i < element.data_used; ++i)
			data_array[i] = element.data_array[i];

		data_used = element.data_used;
	};

	void Concatenate(const FastVector& element)
	{
		int new_size = data_used + element.data_used;

		if (new_size > data_capacity)
			Resize(new_size);

		for (int i = 0; i < element.data_used; ++i)
			data_array[i] = element.data_array[i];

		data_used = new_size;
	};

	void FreeData(){ FAST_DEL_ARRAY(data_array); data_capacity = 0; data_used = 0; }

private:
	TYPE *    data_array = nullptr;
	Fuint     data_capacity = 0;

	Fuint     data_used = 0;

	const int chunk_size = 50;
};

// ---------------------------------------------------------------------------------------------------------

namespace FastInternal
{
	// -----------------------------------------------------------------------------------------------------
	// Forward declarations --------------------------------------------------------------------------------

	class FastMain;

	class FastCreation;
	enum  FastElementType;
	class FastElement;
	class FastWindow;

	class FastIO;
	enum  FastKeyMapping;

	class FastStyle;
	struct FastStyleColours;
	struct FastStylePhyisical;

	class FastFonts;
	class FastFont;
	class FastGlyph;

	class FastDraw;
	class FastDrawShape;

	class FastElements;

	// -----------------------------------------------------------------------------------------------------
	// Internal classes ------------------------------------------------------------------------------------

	// ----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// Fonts
	//-----------------------------------------------------------------------------

	class FastFont
	{
	public:
		FastFont(stbtt_fontinfo font_info);
		~FastFont();

		void CleanUp();

		void SetFontScale(float set);
		float GetFontScale();

		FastGlyph GetGlyphByChar(TR_uchar c);

	public:
		TR_uchar*  texture_data = nullptr;
		TR_uint    texture_id = 0;
		FastVec2 size = FastVec2(0, 0);

		FastVector<FastGlyph> glyphs;

	private:
	

	private:
		stbtt_fontinfo info;
		float		   scale = 0.0f;
	};

	class FastGlyph
	{
	public:
		FastGlyph();

		FastVec2 uvs_x0;
		FastVec2 uvs_y0;
		FastVec2 uvs_x1;
		FastVec2 uvs_y1;

		float    ratio_x_y = 0.0f;
	};

	enum FastFontRange
	{
		FAST_FONT_RANGE_LATIN,
		FAST_FONT_RANGE_KOREAN,
		FAST_FONT_RANGE_CHINESE,
		FAST_FONT_RANGE_JAPANESE,
		FAST_FONT_RANGE_CYRILLIC,
		FAST_FONT_RANGE_THAI,
	};

	class FastFonts 
	{
	public:
		FastFonts();
		~FastFonts();

		void Start();
		void CleanUp();

		void LoadFont(const char* path, int font_size, FastFontRange range = FastFontRange::FAST_FONT_RANGE_LATIN);

		FastFont* GetCurrFont() const;

	private:
		FastVec2 TexturePosToUV(FastVec2 texture_size, FastVec2 pos);

		std::vector<FastVec2> GetBaseGlyphsRanges();
		std::vector<FastVec2> GetLatinGlyphsRanges();
		std::vector<FastVec2> GetKoreanGlyphsRanges();
		std::vector<FastVec2> GetChineseGlyphsRanges();
		std::vector<FastVec2> GetJapaneseGlyphsRanges();
		std::vector<FastVec2> GetCyrillicGlyphsRanges();
		std::vector<FastVec2> GetThaiGlyphsRanges();

	private:
		FastFont* curr_font = nullptr;
	};

	// ----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// Draw
	//-----------------------------------------------------------------------------

	class FastDrawShape
	{
	public:
		FastDrawShape();

		void AddPoint(FastVec2 point_pos);
		void AddTextureId(TR_uint id);
		void Finish(FastColour colour);
		void Finish(FastColour colour, FastVec4 range_uvs);
		void Clear();
		void SetClippingRect(const FastRect& rect);

		TR_uint* GetIndicesPtr();
		FastVector<TR_uint> GetIndices();
		TR_uint GetIndicesCount();
		float* GetVerticesPtr();
		FastVector<float> GetVertices();
		float* GetColoursPtr();
		FastVector<float> GetColours();
		float* GetUvsPtr();
		FastVector<float> GetUvs();
		float* GetVerticesColourUvsPtr();
		FastVector<float> GetVerticesColoursUvs();

		bool GetUsesClippingRect() const;
		FastRect GetClippingRect() const;

		TR_uint GetTextureId();

		TR_uint Offset();
		TR_uint VerticesOffset() const;
		TR_uint VerticesSize() const;
		TR_uint ColourOffset() const;
		TR_uint ColoursSize() const;
		TR_uint UvsOffset() const;
		TR_uint UvsSize() const;

	private:
		FastVector<TR_uint>   indices;
		FastVector<float>     vertices;
		FastVector<float>     colours;
		FastVector<float>     uvs;
		FastVector<float>     vertices_colour_uvs;

		TR_uint				  curr_indices_count = 0;

		TR_uint                 texture_id = 0;

		bool				  finished = false;
		FastVector<FastVec2> points;

		bool				  uses_clipping_rect = false;
		FastRect			  clipping_rect;

		FastVec4			  quad_size;
	};

	enum FastDrawTextAlign
	{
		FAST_DRAW_TEXT_ALIGN_LEFT,
		FAST_DRAW_TEXT_ALIGN_CENTER,
		FAST_DRAW_TEXT_ALIGN_RIGHT,
	};

	struct FastDrawTextLineInfo
	{
		float x_size = 0;
		TR_uint max_word = 0;
	};

	class FastDraw 
	{
	public:
		 FastDraw();
		~FastDraw();

		void Start();
		void CleanUp();

		void DrawDebug();
		FastVector<FastDrawShape>& GetDebugShapes();

		void FontAtlas(FastVec2 pos, FastVec2 size, FastFont* font, FastColour colour);
		void Text(FastVec2 pos, float size, FastFont* font, std::string text, FastColour colour);
		void Text(FastVec2 pos, FastVec2 size, FastFont* font, std::string text, FastDrawTextAlign align, bool overflow, FastColour colour);

	private:
		FastVector<FastDrawShape> debug_shapes;

		bool	      drawing_shape = false;
		FastDrawShape curr_shape;

		bool	      clipping_enabled = false;
		FastRect      curr_clipping_rect;
	};

	// ----------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------------------
}

namespace TextRenderer
{
	// -----------------------------------------------------------------------------------------------------
	// User exposed functions ------------------------------------------------------------------------------

	const char* GetVersion();

	void LoadFont(const char* filepath);

	// -----------------------------------------------------------------------------------------------------
}


#endif // !_TEXT_RENDERER
