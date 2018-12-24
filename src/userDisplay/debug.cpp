#include "ncrapi/userDisplay/userDisplay.hpp"

namespace ncrapi
{
void UserDisplay::createDebug(lv_obj_t *parent)
{

    createUserObj(OBJ_BTNM_SON, false, "DebugPage", parent);
}
} // namespace ncrapi