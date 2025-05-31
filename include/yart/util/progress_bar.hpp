#pragma once

#include <mutex>
#include <string>

// Full block ASCII code "\u2588"
namespace yart {
  namespace util {
    class ProgressBar {
    private:
      std::mutex update_lock;

      float total_progress;
      std::string progress_char;
      float current_progress;
      int current_pos = 0;
      int progress_bar_width;

      bool show_percentage;

      void update_bar();

    public:
      ProgressBar(float _total_progress, int bar_width = 50, std::string _progress_char = "\u2588",
                  bool _show_percentage = false);
      ~ProgressBar() = default;

      void increment_progress(float increment);

      void end();

      ProgressBar& set_show_percentage(bool show);
      ProgressBar& set_total_progress(float total_progress);
      ProgressBar& set_progress(float progress);
      ProgressBar& set_bar_width(int width);
      ProgressBar& set_progress_char(std::string _progress_char);
    };
  }  // namespace util
}  // namespace yart