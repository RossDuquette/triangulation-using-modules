#include <assert.h>

#include "measured-dist.h"

MeasuredDistMsg::MeasuredDistMsg() :
    num_beacons(*(int*) data)
{
    const int SIZE_PER_BEACON = sizeof(*x_list) + sizeof(*y_list)
                                + sizeof(*radius_list);
    const int MAX_NUM_BEACONS = (MAX_MSG_LEN - sizeof(num_beacons))
                                / SIZE_PER_BEACON;

    int len = sizeof(num_beacons);

    x_list = (float*) &data[len];
    len += sizeof(*x_list) * MAX_NUM_BEACONS;

    y_list = (float*) &data[len];
    len += sizeof(*y_list) * MAX_NUM_BEACONS;

    radius_list = (float*) &data[len];
    len += sizeof(*radius_list) * MAX_NUM_BEACONS;

    assert(len <= MAX_MSG_LEN);
}
