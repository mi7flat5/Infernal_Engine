#include "Engine.h"
#include <QtWidgets>

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { EDITOR_LOG("error saving file") }
#endif