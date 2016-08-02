# Trazh-PA

This is a personal project for all kinds of combined functionality. 

# Dependencies

Currently there are 2 dependencies in the project that would need to be set up before working with a clone:
1. libcurl v. 7.50.0
2. TinyXML-2 v. 3.0.0

libcurl is a build as a static library and can be included as you like as long as it can be included with:
>#include <curl\curl.h>

TinyXML-2 is a header-only and should be located in a with a path from the root so it can be include with:
>#include "Dependencies\TinyXML-2\tinyxml2.h"