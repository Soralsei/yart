#include "yart/util/progress_bar.hpp"

#include <cstdint>
#include <iomanip>  // for setw, setprecision, setfill
#include <iostream>
#include <mutex>
#include <ostream>

namespace yart {
  namespace util {
    ProgressBar::ProgressBar(float _total_progress, int bar_width, std::string _progress_char,
                             bool _show_percentage)
        : total_progress(_total_progress),
          progress_char(_progress_char),
          current_progress(0),
          progress_bar_width(bar_width),
          show_percentage(_show_percentage) {
#ifdef _DEBUG
      std::cerr << "Total progress : " << total_progress << '\n';
      std::cerr << "progress_char : " << progress_char << '\n';
      std::cerr << "progress_bar_width : " << progress_bar_width << '\n';
#endif
    }

    void ProgressBar::increment_progress(float increment) {
      std::scoped_lock lock{update_lock};
      current_progress += increment;
      update_bar();
    }

    void ProgressBar::update_bar() {
      int updated_pos = static_cast<int>(static_cast<float>(progress_bar_width)
                                         * (current_progress / total_progress));
      if (updated_pos > current_pos) {
        current_pos = updated_pos;
        std::cout << "[";
        for (int i = 0; i < current_pos; ++i) {
          std::cout << progress_char;
        }
        for (int i = current_pos; i < progress_bar_width; ++i) {
          std::cout << " ";
        }
        std::cout << "] " << std::fixed;
        if (show_percentage) {
          std::cout << std::setprecision(1) << current_progress / total_progress * 100.0f << "% ";
        }
        std::cout << "(" << static_cast<uint32_t>(current_progress) << '/'
                  << static_cast<uint32_t>(total_progress) << ")\r" << std::flush;
      }
    }

    ProgressBar& ProgressBar::set_show_percentage(bool show) {
      std::scoped_lock lock{update_lock};
      show_percentage = show;
      return *this;
    }
    ProgressBar& ProgressBar::set_total_progress(float _total_progress) {
      std::scoped_lock lock{update_lock};
      total_progress = _total_progress;
      update_bar();
      return *this;
    }
    ProgressBar& ProgressBar::set_progress(float _progress) {
      std::scoped_lock lock{update_lock};
      current_progress = _progress;
      return *this;
    }
    ProgressBar& ProgressBar::set_bar_width(int _width) {
      std::scoped_lock lock{update_lock};
      progress_bar_width = _width;
      return *this;
    }
    ProgressBar& ProgressBar::set_progress_char(std::string _progress_char) {
      std::scoped_lock lock{update_lock};
      progress_char = _progress_char;
      return *this;
    }

    void ProgressBar::end() { std::cout << '\n'; }

  }  // namespace util
}  // namespace yart