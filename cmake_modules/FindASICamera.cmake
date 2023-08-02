find_library(ASICAMERA_LIBRARIES NAMES ASICamera2 DOC "ZWO ASI Camera Library")

message(ASICAMERA_LIBRARIES="${ASICAMERA_LIBRARIES}")

find_path(ASICAMERA_INCLUDE_DIRS
          NAMES zwo/ASICamera2.h
          DOC "ZWO ASI Camera Library"
          PATH_SUFFIXES zwo)
          
message(ASICAMERA_INCLUDE_DIRS="${ASICAMERA_INCLUDE_DIRS}")

add_library(ASICAMERA_LIBRARY STATIC IMPORTED)

set_target_properties(ASICAMERA_LIBRARY
                        PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                   "${ASICAMERA_INCLUDE_DIRS}"
                                   IMPORTED_LOCATION
                                   "${ASICAMERA_LIBRARIES}")