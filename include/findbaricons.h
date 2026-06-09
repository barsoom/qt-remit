#ifndef FINDBARICONS_H
#define FINDBARICONS_H

#include <QIcon>

class QPalette;

// Vector icons for the find-bar buttons, painted in palette text color
// so they pick up light/dark themes automatically.
class FindBarIcons {
public:
    static QIcon chevronUp(const QPalette& palette);
    static QIcon chevronDown(const QPalette& palette);
    static QIcon close(const QPalette& palette);
};

#endif // FINDBARICONS_H
