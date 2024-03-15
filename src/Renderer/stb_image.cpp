// This source file serves as the implementation point for the stb_image library.
// The STB_IMAGE_IMPLEMENTATION macro enables the inclusion of the implementation
// code for stb_image.h when it's included in this file. This approach is necessary
// because stb_image is a header-only library, and its implementation code needs to be
// compiled exactly once within the project. Including this file in your project ensures
// that you can use stb_image functionalities such as image loading, decoding, and more
// across your project without multiple definitions.
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"