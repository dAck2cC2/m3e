
#define LOG_TAG "Region"

#include <inttypes.h>
#include <limits.h>

#include <utils/Log.h>
#include <utils/String8.h>
//#include <utils/CallStack.h>

#include <ui/Rect.h>
#include <ui/Region.h>
#include <ui/Point.h>

//#include <private/ui/RegionHelper.h>

// ----------------------------------------------------------------------------
#define VALIDATE_REGIONS        (false)
#define VALIDATE_WITH_CORECG    (false)
// ----------------------------------------------------------------------------

#if VALIDATE_WITH_CORECG
//#include <core/SkRegion.h>
#endif

namespace android {
// ----------------------------------------------------------------------------

enum {
    op_or,
    op_xor,
    op_and,
    op_nand,
};

enum {
    direction_LTR,
    direction_RTL
};


// ----------------------------------------------------------------------------

Region::Region() {
}

Region::Region(const Region& rhs)
{
}

Region::Region(const Rect& rhs) {
}

Region::~Region()
{
}


/**
 * Creates a new region with the same data as the argument, but divides rectangles as necessary to
 * remove T-Junctions
 *
 * Note: the output will not necessarily be a very efficient representation of the region, since it
 * may be that a triangle-based approach would generate significantly simpler geometry
 */
Region Region::createTJunctionFreeRegion(const Region& r) {

    Region outputRegion;

    return outputRegion;
}

Region& Region::operator = (const Region& rhs)
{
    return *this;
}

Region& Region::makeBoundsSelf()
{
    return *this;
}

bool Region::contains(const Point& point) const {
    return false;
}

bool Region::contains(int x, int y) const {
    return false;
}

void Region::clear()
{
}

void Region::set(const Rect& r)
{
}

void Region::set(int32_t w, int32_t h)
{
}

void Region::set(uint32_t w, uint32_t h)
{
}

bool Region::isTriviallyEqual(const Region& region) const {
    return false;
}

// ----------------------------------------------------------------------------

void Region::addRectUnchecked(int l, int t, int r, int b)
{
}

// ----------------------------------------------------------------------------

Region& Region::orSelf(const Rect& r) {
    return operationSelf(r, op_or);
}
Region& Region::xorSelf(const Rect& r) {
    return operationSelf(r, op_xor);
}
Region& Region::andSelf(const Rect& r) {
    return operationSelf(r, op_and);
}
Region& Region::subtractSelf(const Rect& r) {
    return operationSelf(r, op_nand);
}
Region& Region::operationSelf(const Rect& r, int op) {
    return *this;
}

// ----------------------------------------------------------------------------

Region& Region::orSelf(const Region& rhs) {
    return operationSelf(rhs, op_or);
}
Region& Region::xorSelf(const Region& rhs) {
    return operationSelf(rhs, op_xor);
}
Region& Region::andSelf(const Region& rhs) {
    return operationSelf(rhs, op_and);
}
Region& Region::subtractSelf(const Region& rhs) {
    return operationSelf(rhs, op_nand);
}
Region& Region::operationSelf(const Region& rhs, int op) {
    return *this;
}

Region& Region::translateSelf(int x, int y) {
    return *this;
}

// ----------------------------------------------------------------------------

const Region Region::merge(const Rect& rhs) const {
    return operation(rhs, op_or);
}
const Region Region::mergeExclusive(const Rect& rhs) const {
    return operation(rhs, op_xor);
}
const Region Region::intersect(const Rect& rhs) const {
    return operation(rhs, op_and);
}
const Region Region::subtract(const Rect& rhs) const {
    return operation(rhs, op_nand);
}
const Region Region::operation(const Rect& rhs, int op) const {
    Region result;
    return result;
}

// ----------------------------------------------------------------------------

const Region Region::merge(const Region& rhs) const {
    return operation(rhs, op_or);
}
const Region Region::mergeExclusive(const Region& rhs) const {
    return operation(rhs, op_xor);
}
const Region Region::intersect(const Region& rhs) const {
    return operation(rhs, op_and);
}
const Region Region::subtract(const Region& rhs) const {
    return operation(rhs, op_nand);
}
const Region Region::operation(const Region& rhs, int op) const {
    Region result;
    return result;
}

const Region Region::translate(int x, int y) const {
    Region result;
    return result;
}

// ----------------------------------------------------------------------------

Region& Region::orSelf(const Region& rhs, int dx, int dy) {
    return operationSelf(rhs, dx, dy, op_or);
}
Region& Region::xorSelf(const Region& rhs, int dx, int dy) {
    return operationSelf(rhs, dx, dy, op_xor);
}
Region& Region::andSelf(const Region& rhs, int dx, int dy) {
    return operationSelf(rhs, dx, dy, op_and);
}
Region& Region::subtractSelf(const Region& rhs, int dx, int dy) {
    return operationSelf(rhs, dx, dy, op_nand);
}
Region& Region::operationSelf(const Region& rhs, int dx, int dy, int op) {
    return *this;
}

// ----------------------------------------------------------------------------

const Region Region::merge(const Region& rhs, int dx, int dy) const {
    return operation(rhs, dx, dy, op_or);
}
const Region Region::mergeExclusive(const Region& rhs, int dx, int dy) const {
    return operation(rhs, dx, dy, op_xor);
}
const Region Region::intersect(const Region& rhs, int dx, int dy) const {
    return operation(rhs, dx, dy, op_and);
}
const Region Region::subtract(const Region& rhs, int dx, int dy) const {
    return operation(rhs, dx, dy, op_nand);
}
const Region Region::operation(const Region& rhs, int dx, int dy, int op) const {
    Region result;
    return result;
}

#if 0
// ----------------------------------------------------------------------------

// This is our region rasterizer, which merges rects and spans together
// to obtain an optimal region.
class Region::rasterizer : public region_operator<Rect>::region_rasterizer
{
    Rect bounds;
    Vector<Rect>& storage;
    Rect* head;
    Rect* tail;
    Vector<Rect> span;
    Rect* cur;
public:
    rasterizer(Region& reg)
        : bounds(INT_MAX, 0, INT_MIN, 0), storage(reg.mStorage), head(), tail(), cur() {
        storage.clear();
    }

    virtual ~rasterizer();

    virtual void operator()(const Rect& rect);

private:
    template<typename T>
    static inline T min(T rhs, T lhs) { return rhs < lhs ? rhs : lhs; }
    template<typename T>
    static inline T max(T rhs, T lhs) { return rhs > lhs ? rhs : lhs; }

    void flushSpan();
};


Region::rasterizer::~rasterizer()
{
}

void Region::rasterizer::operator()(const Rect& rect)
{
}

void Region::rasterizer::flushSpan()
{
}
#endif
bool Region::validate(const Region& reg, const char* name, bool silent)
{
    return false;
}

void Region::boolean_operation(int op, Region& dst,
        const Region& lhs,
        const Region& rhs, int dx, int dy)
{
}

void Region::boolean_operation(int op, Region& dst,
        const Region& lhs,
        const Rect& rhs, int dx, int dy)
{
}

void Region::boolean_operation(int op, Region& dst,
        const Region& lhs, const Region& rhs)
{
}

void Region::boolean_operation(int op, Region& dst,
        const Region& lhs, const Rect& rhs)
{
}

void Region::translate(Region& reg, int dx, int dy)
{
}

void Region::translate(Region& dst, const Region& reg, int dx, int dy)
{
}

// ----------------------------------------------------------------------------

size_t Region::getFlattenedSize() const {
    return sizeof(uint32_t) + sizeof(Rect);
}

status_t Region::flatten(void* buffer, size_t size) const {
    return NO_ERROR;
}

status_t Region::unflatten(void const* buffer, size_t size) {
    return NO_ERROR;
}

// ----------------------------------------------------------------------------

Region::const_iterator Region::begin() const {
    return mStorage.array();
}

Region::const_iterator Region::end() const {
    size_t numRects = isRect() ? 1 : mStorage.size() - 1;
    return mStorage.array() + numRects;
}

Rect const* Region::getArray(size_t* count) const {
    if (count) *count = static_cast<size_t>(end() - begin());
    return begin();
}

// ----------------------------------------------------------------------------

void Region::dump(String8& out, const char* what, uint32_t /* flags */) const
{
}

void Region::dump(const char* what, uint32_t /* flags */) const
{
}

// ----------------------------------------------------------------------------

}; // namespace android
