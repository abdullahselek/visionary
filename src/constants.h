//
// Created by Selek, Abdullah on 16.06.17.
//

#ifndef VISIONARY_CONSTANTS_H
#define VISIONARY_CONSTANTS_H

namespace window {
    const std::string kTarget = "Target";
}

namespace source {
    enum type {
        image,
        video,
        camera
    };
}

namespace tracker {
    enum type {
        MIL,
        BOOSTING
    };

    static const char * TrackerValues[] = { "MIL", "BOOSTING" };
    const char * getCharForEnum(int enumVal) {
        return TrackerValues[enumVal];
    }
}

#endif //VISIONARY_CONSTANTS_H
