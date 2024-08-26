/*******************************************************************************
 * ESP32_JPEG Wrapper Class
 *
 * Dependent libraries:
 * ESP32_JPEG: https://github.com/esp-arduino-libs/ESP32_JPEG.git
 ******************************************************************************/
#pragma once

// #if defined(ESP32)

#define READ_BUFFER_SIZE 4096

#include <ESP32_JPEG_Library.h>
#include <JPEGDEC.h>

class MjpegClass
{
public:
  bool setup(
      FILE *input, uint8_t *mjpeg_buf,
      uint16_t *output_buf, size_t output_buf_size, bool useBigEndian)
  {
    _input = input;
    _mjpeg_buf = mjpeg_buf;
    _output_buf = (uint8_t *)output_buf;
    _output_buf_size = output_buf_size;
    _useBigEndian = useBigEndian;
    _inputindex = 0;

    if (!_read_buf)
    {
      _read_buf = (uint8_t *)malloc(READ_BUFFER_SIZE);
    }

    if (!_read_buf)
    {
      return false;
    }

    return true;
  }
  
  bool setup(
      FILE *input, uint8_t *mjpeg_buf, JPEG_DRAW_CALLBACK *pfnDraw, bool useBigEndian,
      int x, int y, int widthLimit, int heightLimit)
  {
    _input = input;
    _mjpeg_buf = mjpeg_buf;
    _pfnDraw = pfnDraw;
    _useBigEndian = useBigEndian;
    _x = x;
    _y = y;
    _widthLimit = widthLimit;
    _heightLimit = heightLimit;
    _inputindex = 0;

    if (!_read_buf)
    {
      _read_buf = (uint8_t *)malloc(READ_BUFFER_SIZE);
    }

    return true;
  }

  bool readMjpegBuf()
  {
    if (_inputindex == 0)
    {
      _buf_read = fread(_read_buf, 1, READ_BUFFER_SIZE, _input);
      _inputindex += _buf_read;
    }
    _mjpeg_buf_offset = 0;
    int i = 0;
    bool found_FFD8 = false;
    while ((_buf_read > 0) && (!found_FFD8))
    {
      i = 0;
      while ((i < _buf_read) && (!found_FFD8))
      {
        if ((_read_buf[i] == 0xFF) && (_read_buf[i + 1] == 0xD8)) // JPEG header
        {
          // Serial.printf("Found FFD8 at: %d.\n", i);
          found_FFD8 = true;
        }
        ++i;
      }
      if (found_FFD8)
      {
        --i;
      }
      else
      {
        _buf_read = fread(_read_buf, 1, READ_BUFFER_SIZE, _input);
      }
    }
    uint8_t *_p = _read_buf + i;
    _buf_read -= i;
    bool found_FFD9 = false;
    if (_buf_read > 0)
    {
      i = 3;
      while ((_buf_read > 0) && (!found_FFD9))
      {
        if ((_mjpeg_buf_offset > 0) && (_mjpeg_buf[_mjpeg_buf_offset - 1] == 0xFF) && (_p[0] == 0xD9)) // JPEG trailer
        {
          // Serial.printf("Found FFD9 at: %d.\n", i);
          found_FFD9 = true;
        }
        else
        {
          while ((i < _buf_read) && (!found_FFD9))
          {
            if ((_p[i] == 0xFF) && (_p[i + 1] == 0xD9)) // JPEG trailer
            {
              found_FFD9 = true;
              ++i;
            }
            ++i;
          }
        }

        // Serial.printf("i: %d\n", i);
        memcpy(_mjpeg_buf + _mjpeg_buf_offset, _p, i);
        _mjpeg_buf_offset += i;
        size_t o = _buf_read - i;
        if (o > 0)
        {
          // Serial.printf("o: %d\n", o);
          memcpy(_read_buf, _p + i, o);
          _buf_read = fread(_read_buf + o, 1, READ_BUFFER_SIZE - o, _input);
          _p = _read_buf;
          _inputindex += _buf_read;
          _buf_read += o;
          // Serial.printf("_buf_read: %d\n", _buf_read);
        }
        else
        {
          _buf_read = fread(_read_buf, 1, READ_BUFFER_SIZE, _input);
          _p = _read_buf;
          _inputindex += _buf_read;
        }
        i = 0;
      }
      if (found_FFD9)
      {
        return true;
      }
    }

    return false;
  }

  bool decodeJpg()
  {
    _remain = _mjpeg_buf_offset;

    // Generate default configuration
    jpeg_dec_config_t config = {
        .output_type = JPEG_RAW_TYPE_RGB888,
        .rotate = JPEG_ROTATE_0D,
    };
    // Create jpeg_dec
    _jpeg_dec = jpeg_dec_open(&config);

    // Create io_callback handle
    _jpeg_io = (jpeg_dec_io_t *)calloc(1, sizeof(jpeg_dec_io_t));

    // Create out_info handle
    _out_info = (jpeg_dec_header_info_t *)calloc(1, sizeof(jpeg_dec_header_info_t));

    // Set input buffer and buffer len to io_callback
    _jpeg_io->inbuf = _mjpeg_buf;
    _jpeg_io->inbuf_len = _remain;

    jpeg_dec_parse_header(_jpeg_dec, _jpeg_io, _out_info);

    _w = _out_info->width;
    _h = _out_info->height;

    if ((_w * _h * 2) > _output_buf_size)
    {
      return false;
    }
    _jpeg_io->outbuf = _output_buf;

    jpeg_dec_process(_jpeg_dec, _jpeg_io);
    jpeg_dec_close(_jpeg_dec);

    free(_jpeg_io);
    free(_out_info);

    return true;
  }
  bool drawJpg()
  {
    _remain = _mjpeg_buf_offset;
    _jpeg.openRAM(_mjpeg_buf, _remain, _pfnDraw);
    if (_scale == -1)
    {
      // scale to fit height
      int iMaxMCUs;
      int w = _jpeg.getWidth();
      int h = _jpeg.getHeight();
      float ratio = (float)h / _heightLimit;
      if (ratio <= 1)
      {
        _scale = 0;
        iMaxMCUs = _widthLimit / 16;
      }
      else if (ratio <= 2)
      {
        _scale = JPEG_SCALE_HALF;
        iMaxMCUs = _widthLimit / 8;
        w /= 2;
        h /= 2;
      }
      else if (ratio <= 4)
      {
        _scale = JPEG_SCALE_QUARTER;
        iMaxMCUs = _widthLimit / 4;
        w /= 4;
        h /= 4;
      }
      else
      {
        _scale = JPEG_SCALE_EIGHTH;
        iMaxMCUs = _widthLimit / 2;
        w /= 8;
        h /= 8;
      }
      _jpeg.setMaxOutputSize(iMaxMCUs);
      _x = (w > _widthLimit) ? 0 : ((_widthLimit - w) / 2);
      _y = (_heightLimit - h) / 2;
    }
    if (_useBigEndian)
    {
      _jpeg.setPixelType(RGB565_BIG_ENDIAN);
    }
    _jpeg.decode(_x, _y, _scale);
    _jpeg.close();

    return true;
  }

  int16_t getWidth()
  {
    return _w;
  }

  int16_t getHeight()
  {
    return _h;
  }

  void close()
  {
    fclose(_input);
  }

private:
  FILE *_input;
  uint8_t *_mjpeg_buf;
  uint8_t *_output_buf;
  size_t _output_buf_size;
  bool _useBigEndian;

  uint8_t *_read_buf;
  int32_t _mjpeg_buf_offset = 0;

  jpeg_dec_handle_t *_jpeg_dec;
  jpeg_dec_io_t *_jpeg_io;
  jpeg_dec_header_info_t *_out_info;

  int16_t _w = 0, _h = 0;

  int32_t _inputindex = 0;
  int32_t _buf_read;
  int32_t _remain = 0;

  JPEG_DRAW_CALLBACK *_pfnDraw;
  int _x;
  int _y;
  int _widthLimit;
  int _heightLimit;

  JPEGDEC _jpeg;
  int _scale = -1;
};

// #endif // defined(ESP32)