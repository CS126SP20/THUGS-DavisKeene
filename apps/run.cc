// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "my_app.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace app {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("THUGS: v.0.1");
}

}  // namespace app


// This is a macro that runs the application.
CINDER_APP(app::THUGApp,
           RendererGl(RendererGl::Options().msaa(app::kSamples)),
           app::SetUp)
