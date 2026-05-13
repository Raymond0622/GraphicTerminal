#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include "ftxui/component/app.hpp"             // for App// for ftxui
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"  // for Elements, Element, operator|, separator, text, focusPositionRelative, size, border, flex, frame, bgcolor, gridbox, vbox, EQUAL, center, HEIGHT, WIDTH
#include "ftxui/screen/color.hpp"  // for Color
#include "ftxui/component/app.hpp"             // for App
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for ButtonOption
#include "ftxui/dom/elements.hpp"  // for gauge, separator, text, vbox, operator|, Element, border
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Green, Color::Red
 
int main() {
    std::vector<cv::Mat> frames;
    char buffer[1000];
    for (int i = 0; i < 15;i++) {
        std::sprintf(buffer, "/Users/raymondpark/Downloads/ezgif-split/frame_%02d_delay-0.1s.png", i);
        std::string path = buffer;
        cv::Mat img = cv::imread(path, cv::IMREAD_COLOR), act;
        cv::resize(img, act, cv::Size(), 0.1, 0.1, cv::INTER_AREA);
        frames.push_back(std::move(act));
    }
    std::size_t current = 0;
    bool playing = true;
    int fps = 12;
    std::thread play([&] {
        while (true) {
            if (playing) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000/fps));
                current++;
                current %= frames.size();
            }
        }
    });
    auto screen = ftxui::ScreenInteractive::FitComponent();

    auto component = ftxui::Renderer([&] {
        const cv::Mat& img = frames[current];
        ftxui::Elements rows;   
        for (int y = 0; y < img.rows; y++) {
            ftxui::Elements cols;
            for (int x = 0; x < img.cols; x++) {
                cv::Vec3b p = img.at<cv::Vec3b>(y, x);
                cols.push_back(
                    ftxui::text("  ") | ftxui::bgcolor(ftxui::Color::RGB(p[2], p[1], p[0]))
                );
            }

            rows.push_back(ftxui::hbox(std::move(cols)));
        }
        return ftxui::vbox(std::move(rows));
        //ftxui::Canvas c(C, R);
        // for (int y = 0; y < R; y++) {
        //     for (int x = 0; x < C; x++) {
        //         cv::Vec3b p = img.at<cv::Vec3b>(y, x);

        //         c.DrawPoint(
        //             x, y,
        //             true,
        //             ftxui::Color::RGB(p[2], p[1], p[0])
        //         );
        //     }
        // }
        // return canvas(std::move(c));
    });

    // ✔ Event handling MUST be attached to Component
    component = component | ftxui::CatchEvent([&](ftxui::Event e) {
        if (e == ftxui::Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(component);
}