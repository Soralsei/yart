#pragma once

#include <libpng/png.h>
#include <sys/types.h>

#include <cstddef>
#include <cstdio>
#include <iostream>

#include "pngconf.h"
#include "yart/file/image_writer.hpp"
#include "yart/image/color.hpp"

namespace yart {
  namespace file {
    template <typename ColorFormat> class PNGWriter : public ImageWriter {
    private:
      ColorFormat color_format;

      png_structp m_png_write_struct = nullptr;
      png_infop m_png_info = nullptr;

      FILE* m_file = nullptr;
      png_bytepp m_rows = nullptr;
      typename ColorFormat::FormatType* m_raw_data = nullptr;

      int m_color_type;
      int m_bit_depth;
      int transforms;

      static void png_error_fn(png_structp _, png_const_charp error_msg) {
        throw std::runtime_error(error_msg);
      }

      bool open_file(const char* filename) {
        m_file = fopen(filename, "wb");
        if (m_file == nullptr) {
          std::cerr << " Error: fail to open file" << '\n';
          return false;
        }
        return true;
      }
      bool create_png_structs() {
        m_png_write_struct = png_create_write_struct(
            PNG_LIBPNG_VER_STRING, nullptr, &PNGWriter<ColorFormat>::png_error_fn, nullptr);
        if (m_png_write_struct == nullptr) {
          std::cerr << "Error: failed to create PNG write struct" << "\n";
          return false;
        }

        m_png_info = png_create_info_struct(m_png_write_struct);
        if (m_png_info == nullptr) {
          std::cerr << "Error: failed to create PNG info struct" << "\n";
          png_destroy_write_struct(&m_png_write_struct, nullptr);
          return false;
        }

        return true;
      }

      void init_png_structs(int width, int height) {
        png_init_io(m_png_write_struct, m_file);
        png_set_IHDR(m_png_write_struct, m_png_info, width, height, m_bit_depth, m_color_type,
                     PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
      }

      void write_data(const color::Color* color_data, int width, int height) {
        // Create a buffer to hold the pixel data in the desired format
        m_raw_data = new typename ColorFormat::FormatType[width * height]();
        for (int y = 0; y < height; y++) {
          for (int x = 0; x < width; x++) {
            int index = y * width + x;
            m_raw_data[index] = color_format.colorToFormat(color_data[index]);
          }
        }
        m_rows = new png_bytep[static_cast<size_t>(height)];
        for (int i = 0; i < height; i++) {
          m_rows[i] = reinterpret_cast<png_bytep>(m_raw_data + i * width);
        }
        png_set_rows(m_png_write_struct, m_png_info, m_rows);
        png_write_png(m_png_write_struct, m_png_info, transforms, nullptr);

        // Delete raw pixel data and libpng row buffer
        delete[] m_raw_data;
        m_raw_data = nullptr;

        // Delete libpng row buffer
        delete[] m_rows;
        m_rows = nullptr;
      }

      void cleanup_png_structs() {
        if (m_png_write_struct == nullptr) {
          throw std::runtime_error("PNG write struct pointer is null ?");
        }
        if (m_png_info == nullptr) {
          throw std::runtime_error("PNG info struct pointer is null ?");
        }
        if (m_png_write_struct) {
          png_destroy_write_struct(&m_png_write_struct, &m_png_info);
          m_png_write_struct = nullptr;
          m_png_info = nullptr;
        }
      }

    public:
      PNGWriter() {
        if (color_format.channelCount() == 3) {
          m_color_type = PNG_COLOR_TYPE_RGB;
          // Removes filler bytes after color channels (ex: for RGB = 0xAB08E100 -> 0xAB08E1)
          transforms = PNG_TRANSFORM_STRIP_FILLER_AFTER;  // RGB data still has a 0x00 byte after
                                                          // color channels (no uint24_t type)
        } else {
          m_color_type = PNG_COLOR_TYPE_RGBA;
          transforms = PNG_TRANSFORM_IDENTITY;  // No transformation to raw pixel data
        }
        m_bit_depth = color_format.bitDepth();
      }
      ~PNGWriter() = default;
      bool write(const char* filename, const color::Color* data, int width, int height) override {
        if (!open_file(filename)) {
          return false;
        }

        if (!create_png_structs()) {
          if (m_file) {
            fclose(m_file);
            m_file = nullptr;
          }
          return false;
        }
        bool ret = true;

        try {
          init_png_structs(width, height);
          write_data(data, width, height);
          cleanup_png_structs();  // throws if m_png_write_struct or m_png_info is null
        } catch (const std::exception& e) {
          std::cerr << " Error: " << e.what() << '\n';
          ret = false;
        }

        if (m_file) {
          fclose(m_file);
          m_file = nullptr;
        }
        return ret;
      }
    };

  }  // namespace file

}  // namespace yart
