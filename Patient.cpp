#include "Patient.h"
#include <algorithm>
#include <iterator>
#include <set>
class Patient;

//Orders the patients priority
bool operator<(const Patient& first, const Patient& second)
{
    if (first.getPriority() < second.getPriority())
        return true;
    else if (first.getPriority() > second.getPriority())
        return true;
    else
        return false;
}
