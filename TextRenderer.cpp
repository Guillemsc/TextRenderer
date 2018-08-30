#include "TextRenderer.h"

static FastInternal::FastMain* fast_main = nullptr;

FastVec2::FastVec2()
{
	x = 0.0f;
	y = 0.0f;
}

FastVec2::FastVec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

FastVec2 FastVec2::operator+(const FastVec2 & vec)
{
	return FastVec2(x + vec.x, y + vec.y);
}

FastVec2 FastVec2::operator-(const FastVec2 & vec)
{
	return FastVec2(x - vec.x, y - vec.y);
}

FastVec2 FastVec2::operator*(const FastVec2 & vec)
{
	return FastVec2(x * vec.x, y * vec.y);
}

FastVec2 FastVec2::operator*(int val)
{
	return FastVec2(x * val, y *val);
}

FastVec2 FastVec2::operator*(float val)
{
	return FastVec2(x * val, y *val);
}

FastVec2 FastVec2::operator/(const FastVec2 & vec)
{
	FastVec2 ret;

	if (vec.x != 0)
		ret.x = x / vec.x;

	if (vec.y != 0)
		ret.y = y / vec.y;

	return ret;
}

void FastVec2::operator+=(const FastVec2 & vec)
{
	x += vec.x;
	y += vec.y;
}

void FastVec2::operator-=(const FastVec2 & vec)
{
	x -= vec.x;
	y -= vec.y;
}

void FastVec2::operator*=(const FastVec2 & vec)
{
	x *= vec.x;
	y *= vec.y;
}

void FastVec2::operator/=(const FastVec2 & vec)
{
	if (vec.x != 0)
		x /= vec.x;

	if (vec.y != 0)
		y /= vec.y;
}

float FastVec2::Distance(const FastVec2 & vec)
{
	float dist_x = vec.x - x;
	float dist_y = vec.y - y;

	return sqrt(fabs((dist_x * dist_x) + (dist_y * dist_y)));
}

FastVec3::FastVec3()
{
}

FastVec3::FastVec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

FastVec3 FastVec3::operator+(const FastVec3 & vec)
{
	return FastVec3(x + vec.x, y + vec.y, z + vec.z);
}

FastVec3 FastVec3::operator-(const FastVec3 & vec)
{
	return FastVec3(x - vec.x, y - vec.y, z - vec.z);
}

void FastVec3::operator+=(const FastVec3 & vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

void FastVec3::operator-=(const FastVec3 & vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

void FastVec3::operator*=(const FastVec3 & vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
}

void FastVec3::operator/=(const FastVec3 & vec)
{
	if (vec.x != 0)
		x /= vec.x;

	if (vec.y != 0)
		y /= vec.y;

	if (vec.z != 0)
		z /= vec.z;
}

float FastVec3::Distance(const FastVec3 & vec)
{
	float dist_x = vec.x - x;
	float dist_y = vec.y - y;
	float dist_z = vec.z - z;

	return sqrt(fabs((dist_x * dist_x) + (dist_y * dist_y) + (dist_z * dist_z)));
}

FastVec4::FastVec4()
{
	x = 0;
	y = 0;
	w = 0;
	z = 0;
}

FastVec4::FastVec4(float _x, float _y, float _w, float _z)
{
	x = _x;
	y = _y;
	w = _w;
	z = _z;
}

FastVec4 FastVec4::operator+(const FastVec4 & vec)
{
	return FastVec4(x + vec.x, y + vec.y, w + vec.w, z + vec.z);
}

FastVec4 FastVec4::operator-(const FastVec4 & vec)
{
	return FastVec4(x - vec.x, y - vec.y, w - vec.w, z - vec.z);
}

void FastVec4::operator+=(const FastVec4 & vec)
{
	x += vec.x;
	y += vec.y;
	w += vec.w;
	z += vec.z;
}

void FastVec4::operator-=(const FastVec4 & vec)
{
	x -= vec.x;
	y -= vec.y;
	w -= vec.w;
	z -= vec.z;
}

void FastVec4::operator*=(const FastVec4 & vec)
{
	x *= vec.x;
	y *= vec.y;
	w *= vec.w;
	z *= vec.z;
}

void FastVec4::operator/=(const FastVec4 & vec)
{
	if (vec.x != 0)
		x /= vec.x;

	if (vec.y != 0)
		y /= vec.y;

	if (vec.w != 0)
		w = vec.w;

	if (vec.z != 0)
		z /= vec.z;
}

float FastRect::xw()
{
	return x + w;
}

float FastRect::yh()
{
	return y + h;
}

FastVec2 FastRect::Pos()
{
	return FastVec2(x, y);
}

FastVec2 FastRect::Size()
{
	return FastVec2(w, h);
}

FastVec2 FastRect::Center()
{
	return FastVec2(x + (w * 0.5f), y + (h * 0.5f));
}

bool FastRect::Overlaps(FastRect rect)
{
	if (xw() > rect.x && yh() > rect.y && x < rect.xw() && y < rect.yh())
		return true;
	return false;
}

bool FastRect::Contains(FastRect rec)
{
	if (x < rec.x && xw() > rec.xw() && y < rec.y && yh() > rec.yh())
		return true;
	return false;
}

bool FastRect::Contains(FastVec2 point)
{
	if (point.x >= x && point.x <= xw() && point.y >= y && point.y <= yh())
		return true;
	return false;
}

void FastRect::Scissor(FastRect rec)
{
	
}

FastColour::FastColour()
{
}

FastColour::FastColour(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
	a = 1.0f;
}

FastColour::FastColour(const FastVec4 & vec)
{
	r = vec.x;
	g = vec.y;
	b = vec.w;
	a = vec.z;
}

FastColour::FastColour(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

FastColour::FastColour(int hexadecimal_val)
{	
	r = ((hexadecimal_val >> 16) & 0xFF) / 255.0f;
	g = ((hexadecimal_val >> 8) & 0xFF) / 255.0f;
	b = ((hexadecimal_val) & 0xFF) / 255.0f;
}

FastColour FastColour::operator+(const FastColour & vec)
{
	return FastColour(r + vec.r, g + vec.g, b + vec.b, a + vec.a);
}

FastColour FastColour::operator-(const FastColour & vec)
{
	return FastColour(r - vec.r, g - vec.g, b - vec.b, a - vec.a);
}

void FastColour::operator+=(const FastColour & vec)
{
	r += vec.r;
	g += vec.g;
	b += vec.b;
	a += vec.a;
}

void FastColour::operator-=(const FastColour & vec)
{
	r -= vec.r;
	g -= vec.g;
	b -= vec.b;
	a -= vec.a;
}

void FastColour::operator*=(const FastColour & vec)
{
	r *= vec.r;
	g *= vec.g;
	b *= vec.b;
	a *= vec.a;
}

void FastColour::operator/=(const FastColour & vec)
{
	if (vec.r != 0)
		r /= vec.r;

	if (vec.g != 0)
		g /= vec.g;

	if (vec.b != 0)
		b /= vec.b;

	if (vec.a != 0)
		a /= vec.a;
}

FastRect::FastRect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

FastRect::FastRect(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

FastRect::FastRect(const FastVec4 & vec)
{
	x = vec.x;
	y = vec.y;
	w = vec.w;
	h = vec.z;
}

FastRect::FastRect(const FastVec2 & pos, const FastVec2 size)
{
	x = pos.x;
	y = pos.y;
	w = size.x;
	h = size.y;
}

void FastRect::operator=(const FastRect & rect)
{
	x = rect.x;
	y = rect.y;
	w = rect.w;
	h = rect.h;
}

FastBuffer::FastBuffer()
{
}

FastBuffer::FastBuffer(int size)
{
	SetSize(size);
}

FastBuffer::FastBuffer(int width, int height)
{
	SetSize(width, height);
}

void FastBuffer::SetSize(int _size)
{
	Clear();

	size = _size;

	buffer = new TR_uchar[size];

	Reset();
}

void FastBuffer::SetSize(int _width, int _heigth)
{
	SetSize(_width * _heigth);

	width = _width;
	heigth = _heigth;
}

void FastBuffer::Reset()
{
	if (buffer != nullptr)
	{
		memset(buffer, 1, size);
	}
}

void FastBuffer::Clear()
{
	if (buffer != nullptr)
		TR_DEL_ARRAY(buffer);

	buffer = nullptr;
}

void FastBuffer::AddData(int data_ptr_pos, TR_uchar * data)
{
	TR_uchar* tmp_buffer_ptr = buffer;

	tmp_buffer_ptr += data_ptr_pos;

	memcpy(tmp_buffer_ptr, data, sizeof(data));
}

TR_uchar * FastBuffer::GetBufferData()
{
	return buffer;
}

bool FastBuffer::BufferHasData() const
{
	return buffer != nullptr;
}

int FastBuffer::GetWidth()
{
	return width;
}

int FastBuffer::GetHeight()
{
	return heigth;
}

int FastBuffer::GetSize()
{
	return size;
}

void FastBuffer::FlipUpsideDown()
{
	TR_uint rows = heigth / 2; // Iterate only half the buffer to get a full flip
	TR_uchar * tempRow = new TR_uchar[width * sizeof(TR_uchar)];

	for (unsigned rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		memcpy(tempRow, buffer + rowIndex * width, width * sizeof(TR_uchar));
		memcpy(buffer + rowIndex * width, buffer + (heigth - rowIndex - 1) * width, width * sizeof(TR_uchar));
		memcpy(buffer + (heigth - rowIndex - 1) * width, tempRow, width * sizeof(TR_uchar));
	}

	TR_DEL_ARRAY(tempRow);
}

const char * TextRenderer::GetVersion()
{
	return TEXT_RENDERER_VERSION;
}


void TextRenderer::LoadFont(const char * filepath)
{

}

FastInternal::FastFonts::FastFonts()
{
}

FastInternal::FastFonts::~FastFonts()
{
}

void FastInternal::FastFonts::Start()
{
}

void FastInternal::FastFonts::CleanUp()
{
}

void FastInternal::FastFonts::LoadFont(const char * path, int font_size, FastFontRange range)
{
	FastFont* ret = nullptr;

	stbtt_fontinfo font_info;

	/* load font file */
	long size;
	unsigned char* fontBuffer;

	FILE* fontFile = nullptr;
	fopen_s(&fontFile, path, "rb");
	fseek(fontFile, 0, SEEK_END);
	size = ftell(fontFile); 
	fseek(fontFile, 0, SEEK_SET);

	fontBuffer = new unsigned char[size];

	fread(fontBuffer, size, 1, fontFile);
	fclose(fontFile);

	std::vector<FastVec2> glyph_ranges;

	std::vector<FastVec2> base_range = GetBaseGlyphsRanges();

	glyph_ranges.insert(glyph_ranges.end(), base_range.begin(), base_range.end());

	switch (range)
	{
	case FastInternal::FastFontRange::FAST_FONT_RANGE_LATIN:
	{
		std::vector<FastVec2> latin_range = GetLatinGlyphsRanges();

		glyph_ranges.insert(glyph_ranges.end(), latin_range.begin(), latin_range.end());

		break;
	}

	case FastInternal::FastFontRange::FAST_FONT_RANGE_KOREAN:
	{
		std::vector<FastVec2> korean_range = GetKoreanGlyphsRanges();

		glyph_ranges.insert(glyph_ranges.end(), korean_range.begin(), korean_range.end());

		break;
	}

	}

	if (stbtt_InitFont(&font_info, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0)))
	{
		if (curr_font != nullptr)
			TR_DEL(curr_font);

		ret = new FastFont(font_info);

		int atlas_tex_w = 2048;
		int atlas_tex_h = 1024 * 1.0f; // 25
		FastBuffer buffer(atlas_tex_w, atlas_tex_h);

		if (font_size < 10)
			font_size = 10;
		if (font_size > 200)
			font_size = 200;

		int max_glyphs_to_generate = 600;

		float scale = stbtt_ScaleForPixelHeight(&font_info, font_size);

		int ascent, descent, lineGap;
		stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &lineGap);

		float scaled_ascent = ascent * scale;
		float scaled_descent = descent * scale;
		float scaled_line_gap = lineGap *= scale;

		int total_h = ascent - descent;
		int scaled_total_h = scaled_ascent - scaled_descent;

		int curr_advance = 0;
		int line = 0;

		int glyphs_count = 0;
		for (int r = 0; r < glyph_ranges.size(); ++r)
		{
			FastVec2 curr_range = glyph_ranges[r];

			for (int i = curr_range.x; i < curr_range.y; ++i)
			{
				if (glyphs_count > max_glyphs_to_generate)
					break;

				int gliph_index = i;

				// Get Glyph bitmap size
				int x0, y0, x1, y1;
				stbtt_GetGlyphBitmapBox(&font_info, gliph_index, scale, scale, &x0, &y0, &x1, &y1);
				int glyph_bm_w = x1 - x0;
				int glyph_bm_h = y1 - y0;

				// Get Glyph advance values
				int advance;
				stbtt_GetGlyphHMetrics(&font_info, gliph_index, &advance, 0);
				advance *= scale;

				int kern_advance = stbtt_GetGlyphKernAdvance(&font_info, gliph_index, gliph_index + 1);
				kern_advance *= scale;

				int to_advance = advance + kern_advance;

				// Create a test advance to check glyph texture fiting
				int test_advance = curr_advance + to_advance;

				// Jump to new line if does not fit texture width
				if (test_advance + glyph_bm_w >= atlas_tex_w)
				{
					++line;
					curr_advance = 0;
				}

				// Calculate texture offset
				int to_down = y1 + (scaled_total_h - glyph_bm_h);

				int byteOffset = curr_advance + (line * (scaled_total_h + 1) * atlas_tex_w) + (to_down * atlas_tex_w);

				// Render glyph into texture
				stbtt_MakeGlyphBitmap(&font_info, buffer.GetBufferData() + byteOffset, glyph_bm_w, glyph_bm_h, atlas_tex_w, scale, scale, gliph_index);

				// Get uvs
				float x0_size_x = curr_advance;
				float x0_size_y = (line * (scaled_total_h)-scaled_descent);
				FastVec2 uvs_x0 = TexturePosToUV(FastVec2(atlas_tex_w, atlas_tex_h), FastVec2(x0_size_x, x0_size_y));

				float y1_size_x = curr_advance + glyph_bm_w;
				float y1_size_y = (line * scaled_total_h) + scaled_total_h - scaled_descent;
				FastVec2 uvs_y1 = TexturePosToUV(FastVec2(atlas_tex_w, atlas_tex_h), FastVec2(y1_size_x, y1_size_y));

				FastVec2 uvs_x1 = FastVec2(uvs_y1.x, uvs_x0.y);
				FastVec2 uvs_y0 = FastVec2(uvs_x0.x, uvs_y1.y);

				// Calculate x/y ratio
				float ratio_x_y = 1;
				float ratio_height_down = 0;

				if (scaled_total_h > 0)
					ratio_x_y = (float)glyph_bm_w / (float)scaled_total_h;

				// Advance
				curr_advance += to_advance + font_size * 0.15f;

				// Setup glyph
				FastGlyph glyph;
				glyph.uvs_x0 = uvs_x0;
				glyph.uvs_x1 = uvs_x1;
				glyph.uvs_y0 = uvs_y0;
				glyph.uvs_y1 = uvs_y1;
				glyph.ratio_x_y = ratio_x_y;

				ret->glyphs.PushBack(glyph);

				++glyphs_count;
			}
		}

		buffer.FlipUpsideDown();

		ret->SetFontScale(scale);
		ret->texture_data = buffer.GetBufferData();
		ret->size.x = atlas_tex_w;
		ret->size.y = atlas_tex_h;
		//ret->texture_id = fast_main->load_texture(ret->texture_data, ret->size);

		curr_font = ret;

		buffer.Clear();
	}

	// --------------------------------------
}

FastInternal::FastFont * FastInternal::FastFonts::GetCurrFont() const
{
	return curr_font;
}

FastVec2 FastInternal::FastFonts::TexturePosToUV(FastVec2 texture_size, FastVec2 pos)
{
	FastVec2 ret;

	float x_percentage = 0;
	float y_percentage = 0;

	if(texture_size.x != 0)
		x_percentage = (pos.x) / texture_size.x;

	if (texture_size.y != 0)
		y_percentage = (pos.y) / texture_size.y;

	ret.x = x_percentage;
	ret.y = 1 - y_percentage;

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetBaseGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(0, 32));

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetLatinGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(32, 255));

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetKoreanGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(32, 255));
	ret.push_back(FastVec2(12593, 12643));
	ret.push_back(FastVec2(44032, 55197));

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetChineseGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(32, 255));
	ret.push_back(FastVec2(12288, 12543));
	ret.push_back(FastVec2(12784, 12799));
	ret.push_back(FastVec2(65280, 65519));
	ret.push_back(FastVec2(19968, 40879));

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetJapaneseGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(32, 255));

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetCyrillicGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(32, 255));

	return ret;
}

std::vector<FastVec2> FastInternal::FastFonts::GetThaiGlyphsRanges()
{
	std::vector<FastVec2> ret;

	ret.push_back(FastVec2(32, 255));

	return ret;
}

FastInternal::FastFont::FastFont(stbtt_fontinfo _font_info)
{
	info = _font_info;
}

FastInternal::FastFont::~FastFont()
{
}

void FastInternal::FastFont::CleanUp()
{
}

FastInternal::FastGlyph FastInternal::FastFont::GetGlyphByChar(TR_uchar c)
{
	FastGlyph ret;

	int index = 0;
	index = stbtt_FindGlyphIndex(&info, c);

	if (index < glyphs.Size())
		ret = glyphs[index];
	else if (glyphs.Size() > 0)
		ret = glyphs[0];

	return ret;
}

void FastInternal::FastFont::SetFontScale(float set)
{
	scale = set;
}

float FastInternal::FastFont::GetFontScale()
{
	return scale;
}

FastInternal::FastGlyph::FastGlyph()
{
}

FastInternal::FastDraw::FastDraw()
{
}

FastInternal::FastDraw::~FastDraw()
{
}

void FastInternal::FastDraw::Start()
{

}

void FastInternal::FastDraw::CleanUp()
{

}

FastVector<FastInternal::FastDrawShape>& FastInternal::FastDraw::GetDebugShapes()
{
	return debug_shapes;
}

void FastInternal::FastDraw::FontAtlas(FastVec2 pos, FastVec2 size, FastFont * font, FastColour colour)
{
	int min_x = pos.x;
	int max_x = pos.x + size.x;
	int min_y = pos.y;
	int max_y = pos.y + size.y;

	curr_shape.AddPoint(FastVec2(min_x, min_y));
	curr_shape.AddPoint(FastVec2(min_x, max_y));
	curr_shape.AddPoint(FastVec2(max_x, max_y));
	curr_shape.AddPoint(FastVec2(max_x, min_y));

	curr_shape.AddTextureId(font->texture_id);
	curr_shape.Finish(colour);

	if (clipping_enabled)
		curr_shape.SetClippingRect(curr_clipping_rect);
}

void FastInternal::FastDraw::Text(FastVec2 pos, float size, FastFont* font, std::string text, FastColour colour)
{
	if (font != nullptr)
	{
		FastVec2 curr_pos = pos;

		for (int i = 0; i < text.size(); ++i)
		{
			TR_uchar c = text[i];

			if (c != ' ')
			{
				FastGlyph glph = font->GetGlyphByChar(c);

				int word_width = size * glph.ratio_x_y;

				int min_x = curr_pos.x;
				int max_x = curr_pos.x + word_width;
				int min_y = curr_pos.y;
				int max_y = curr_pos.y + size;

				curr_shape.AddPoint(FastVec2(min_x, min_y));
				curr_shape.AddPoint(FastVec2(min_x, max_y));
				curr_shape.AddPoint(FastVec2(max_x, max_y));
				curr_shape.AddPoint(FastVec2(max_x, min_y));
				curr_shape.Finish(colour, FastVec4(glph.uvs_x0.x, glph.uvs_x0.y, glph.uvs_y1.x, glph.uvs_y1.y));

				curr_pos.x = max_x + (size * 0.11f);
			}
			else
				curr_pos.x += size * 0.25f;
		}

		//curr_shape.AddTextureId(fast_main->fonts->GetCurrFont()->texture_id);

		if (clipping_enabled)
			curr_shape.SetClippingRect(curr_clipping_rect);
	}
}

void FastInternal::FastDraw::Text(FastVec2 pos, FastVec2 size, FastFont * font, std::string text, FastDrawTextAlign align, bool overflow, FastColour colour)
{
	if (font != nullptr)
	{
		FastVec2 curr_pos;

		std::vector<FastDrawTextLineInfo> lines_size_x;

		for (int i = 0; i < text.size(); ++i)
		{
			TR_uchar c = text[i];

			if (c != ' ')
			{
				FastGlyph glph = font->GetGlyphByChar(c);

				int word_width = size.y * glph.ratio_x_y;

				int min_x = curr_pos.x;
				int max_x = curr_pos.x + word_width;
				int min_y = curr_pos.y;
				int max_y = curr_pos.y + size.y;

				curr_pos.x = max_x + (size.y * 0.11f);

				if (!overflow)
				{
					if (max_x > size.x)
					{
						FastDrawTextLineInfo line;
						line.x_size = size.x;
						line.max_word = i;
						lines_size_x.push_back(line);
						curr_pos.x = 0;
					}
				}
			}
			else
				curr_pos.x += size.y * 0.25f;
		}
		FastDrawTextLineInfo line;
		line.x_size = curr_pos.x;
		line.max_word = text.size() - 1;
		lines_size_x.push_back(line);

		curr_pos = pos;
		TR_uint curr_line = 0;
		bool fist_time_advance = true;
		for (int i = 0; i < text.size(); ++i)
		{
			TR_uchar c = text[i];

			if (c != ' ')
			{
				FastGlyph glph = font->GetGlyphByChar(c);

				int word_width = size.y * glph.ratio_x_y;

				int min_x = curr_pos.x;
				int min_y = curr_pos.y;

				if (fist_time_advance)
				{
					switch (align)
					{
					case FastDrawTextAlign::FAST_DRAW_TEXT_ALIGN_RIGHT:
						min_x += size.x - lines_size_x[curr_line].x_size;
						break;
					case FastDrawTextAlign::FAST_DRAW_TEXT_ALIGN_CENTER:
						min_x += (size.x - (lines_size_x[curr_line].x_size)) * 0.5f;
						break;
					}

					fist_time_advance = false;
				}

				int max_x = min_x + word_width;
				int max_y = min_y + size.y;

				curr_shape.AddPoint(FastVec2(min_x, min_y));
				curr_shape.AddPoint(FastVec2(min_x, max_y));
				curr_shape.AddPoint(FastVec2(max_x, max_y));
				curr_shape.AddPoint(FastVec2(max_x, min_y));
				curr_shape.Finish(colour, FastVec4(glph.uvs_x0.x, glph.uvs_x0.y, glph.uvs_y1.x, glph.uvs_y1.y));

				curr_pos.x = max_x + (size.y * 0.11f);

				if (lines_size_x[curr_line].max_word == i)
				{
					fist_time_advance = true;
					curr_pos.x = pos.x;
					curr_pos.y += size.y;
					++curr_line;
				}
			}
			else
				curr_pos.x += size.y * 0.25f;
		}

		//curr_shape.AddTextureId(fast_main->fonts->GetCurrFont()->texture_id);

		if (clipping_enabled)
			curr_shape.SetClippingRect(curr_clipping_rect);
	}
}

FastInternal::FastDrawShape::FastDrawShape()
{
}

void FastInternal::FastDrawShape::AddPoint(FastVec2 point_pos)
{
	points.PushBack(point_pos);

	if (points.Size() == 1)
	{
		quad_size.x = point_pos.x;
		quad_size.w = point_pos.x;
		quad_size.y = point_pos.y;
		quad_size.z = point_pos.y;
	}
	else
	{
		if (point_pos.x < quad_size.x)
			quad_size.x = point_pos.x;

		if (point_pos.x > quad_size.w)
			quad_size.w = point_pos.x;

		if (point_pos.y < quad_size.y)
			quad_size.y = point_pos.y;

		if (point_pos.y > quad_size.z)
			quad_size.z = point_pos.y;
	}
	
}

void FastInternal::FastDrawShape::AddTextureId(TR_uint id)
{
	texture_id = id;
}

void FastInternal::FastDrawShape::Finish(FastColour colour)
{
	if (points.Size() >= 3)
	{		
		finished = true;

		// Vertices, Uvs, Colours

		int num_points = points.Size();

		// Triangulize
		for (int i = 0; i < num_points; i++)
		{
			FastVec2 curr_point = points[i];

			vertices.PushBack(curr_point.x);
			vertices.PushBack(curr_point.y);
			vertices.PushBack(0);

			// Color for vertices
			colours.PushBack(colour.r);
			colours.PushBack(colour.g);
			colours.PushBack(colour.b);
			colours.PushBack(colour.a);

			float x_uv = 0;
			float y_uv = 0;
			
			// Uvs for vertices
			float x_normalized = curr_point.x - quad_size.x;
			float y_normalized = curr_point.y - quad_size.y;

			float x_percentage = (x_normalized) / (quad_size.w - quad_size.x);
			float y_percentage = (y_normalized) / (quad_size.z - quad_size.y);

			x_uv = x_percentage;
			y_uv = 1 - y_percentage;
			
			uvs.PushBack(x_uv);
			uvs.PushBack(y_uv);

			if (i > 1)
			{
				// Indices for triangle
				indices.PushBack(curr_indices_count);
				indices.PushBack(curr_indices_count + i - 1);
				indices.PushBack(curr_indices_count + i);
			}
		}

		//vertices_colour_uvs.insert(vertices_colour_uvs.end(), vertices.begin(), vertices.end());
		//vertices_colour_uvs.insert(vertices_colour_uvs.end(), colours.begin(), colours.end());
		//vertices_colour_uvs.insert(vertices_colour_uvs.end(), uvs.begin(), uvs.end());

		curr_indices_count += num_points;
		points.Clear();
		quad_size = FastVec4();
		
		// -----------------------------------
	}

	points.Clear();
}

void FastInternal::FastDrawShape::Finish(FastColour colour, FastVec4 range_uvs)
{
	if (points.Size() >= 3)
	{
		int num_points = points.Size();

		// Triangulize
		for (int i = 0; i < num_points; i++)
		{
			FastVec2 curr_point = points[i];

			vertices.PushBack(curr_point.x);
			vertices.PushBack(curr_point.y);
			vertices.PushBack(0);

			// Color for vertices
			colours.PushBack(colour.r);
			colours.PushBack(colour.g);
			colours.PushBack(colour.b);
			colours.PushBack(colour.a);

			float ranged_x_uv = 0;
			float ranged_y_uv = 0;

			// Uvs for vertices
			float x_normalized = curr_point.x - quad_size.x;
			float y_normalized = curr_point.y - quad_size.y;

			float x_percentage = (x_normalized) / (quad_size.w - quad_size.x);
			float y_percentage = (y_normalized) / (quad_size.z - quad_size.y);

			float x_uv = x_percentage;
			float y_uv = y_percentage;

			if (x_uv > 0)
			{
				float diff = (1 * (range_uvs.w - range_uvs.x));
				ranged_x_uv = (x_uv * diff) / 1;
			}
			ranged_x_uv += range_uvs.x;

			if (y_uv > 0)
			{
				float diff = ((1 - range_uvs.z) - (1 - range_uvs.y));
				ranged_y_uv = (y_uv * diff) / 1;
			}
			ranged_y_uv = 1 - ranged_y_uv - (1 - range_uvs.y);

			uvs.PushBack(ranged_x_uv);
			uvs.PushBack(ranged_y_uv);

			if (i > 1)
			{
				// Indices for triangle
				indices.PushBack(curr_indices_count);
				indices.PushBack(curr_indices_count + i - 1);
				indices.PushBack(curr_indices_count + i);
			}
		}

		//vertices_colour_uvs.insert(vertices_colour_uvs.end(), vertices.begin(), vertices.end());
		//vertices_colour_uvs.insert(vertices_colour_uvs.end(), colours.begin(), colours.end());
		//vertices_colour_uvs.insert(vertices_colour_uvs.end(), uvs.begin(), uvs.end());

		curr_indices_count += num_points;
		points.Clear();
		quad_size = FastVec4();
		
		// -----------------------------------
	}
}

void FastInternal::FastDrawShape::Clear()
{
	finished = false;

	indices.Clear();
	vertices.Clear();
	colours.Clear();
	uvs.Clear();
	vertices_colour_uvs.Clear();

	points.Clear();
}

void FastInternal::FastDrawShape::SetClippingRect(const FastRect & rect)
{
	clipping_rect = rect;

	if (clipping_rect.w > 0 && clipping_rect.h > 0)
		uses_clipping_rect = true;
}

TR_uint * FastInternal::FastDrawShape::GetIndicesPtr()
{
	TR_uint* ret = nullptr;

	if (indices.Size() > 0)
		ret = indices.Data();
	
	return ret;
}

FastVector<TR_uint> FastInternal::FastDrawShape::GetIndices()
{
	return indices;
}

TR_uint FastInternal::FastDrawShape::GetIndicesCount()
{
	return indices.Size();
}

float * FastInternal::FastDrawShape::GetVerticesPtr()
{
	float* ret = nullptr;

	if (vertices.Size() > 0)
		ret = vertices.Data();
	
	return ret;
}

FastVector<float> FastInternal::FastDrawShape::GetVertices()
{
	return vertices;
}

float * FastInternal::FastDrawShape::GetColoursPtr()
{
	float* ret = nullptr;

	if (colours.Size() > 0)
		ret = colours.Data();

	return ret;
}

FastVector<float> FastInternal::FastDrawShape::GetColours()
{
	return colours;
}

float * FastInternal::FastDrawShape::GetUvsPtr()
{
	float* ret = nullptr;

	if (uvs.Size() > 0)
		ret = uvs.Data();

	return ret;
}

FastVector<float> FastInternal::FastDrawShape::GetUvs()
{
	return uvs;
}

float * FastInternal::FastDrawShape::GetVerticesColourUvsPtr()
{
	float* ret = nullptr;

	if (vertices_colour_uvs.Size() > 0)
		ret = vertices_colour_uvs.Data();

	return ret;
}

FastVector<float> FastInternal::FastDrawShape::GetVerticesColoursUvs()
{
	return vertices_colour_uvs;
}

bool FastInternal::FastDrawShape::GetUsesClippingRect() const
{
	return uses_clipping_rect;
}

FastRect FastInternal::FastDrawShape::GetClippingRect() const
{
	return clipping_rect;
}

TR_uint FastInternal::FastDrawShape::GetTextureId()
{
	return texture_id;
}

TR_uint FastInternal::FastDrawShape::Offset()
{
	return 6;
}

TR_uint FastInternal::FastDrawShape::VerticesOffset() const
{
	return 0;
}

TR_uint FastInternal::FastDrawShape::VerticesSize() const
{
	return 3;
}

TR_uint FastInternal::FastDrawShape::ColourOffset() const
{
	return 3;
}

TR_uint FastInternal::FastDrawShape::ColoursSize() const
{
	return 4;
}

TR_uint FastInternal::FastDrawShape::UvsOffset() const
{
	return 7;
}

TR_uint FastInternal::FastDrawShape::UvsSize() const
{
	return 2;
}
