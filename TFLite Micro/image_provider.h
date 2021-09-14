#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_IMAGE_PROVIDER_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_IMAGE_PROVIDER_H_

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

// This is an abstraction around an image source like a camera, and is expected to return 8-bit sample data
TfLiteStatus GetImage(tflite::ErrorReporter *error_reporter, int image_width,
                      int image_height, int channels, int8_t *image_data);

#endif
