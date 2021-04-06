// Various utility/conversion functions for compatibility with the nghttp2 API.

#ifndef QUICHE_HTTP2_ADAPTER_NGHTTP2_UTIL_H_
#define QUICHE_HTTP2_ADAPTER_NGHTTP2_UTIL_H_

#include <cstdint>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "http2/adapter/http2_protocol.h"
#include "third_party/nghttp2/src/lib/includes/nghttp2/nghttp2.h"
#include "spdy/core/spdy_header_block.h"

namespace http2 {
namespace adapter {

// Return codes to represent various errors.
inline constexpr int kStreamCallbackFailureStatus =
    NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
inline constexpr int kCancelStatus = NGHTTP2_ERR_CANCEL;

uint8_t* ToUint8Ptr(char* str);
uint8_t* ToUint8Ptr(const char* str);

absl::string_view ToStringView(nghttp2_rcbuf* rc_buffer);
absl::string_view ToStringView(uint8_t* pointer, size_t length);

// Returns the nghttp2 header structure from the given request |headers|, which
// must have the correct pseudoheaders preceding other headers.
std::vector<nghttp2_nv> GetRequestNghttp2Nvs(absl::Span<const Header> headers);

// Returns the nghttp2 header structure from the given response |headers|, with
// the :status pseudoheader first based on the given |response_code|. The
// |response_code| is passed in separately from |headers| for lifetime reasons.
std::vector<nghttp2_nv> GetResponseNghttp2Nvs(
    const spdy::Http2HeaderBlock& headers,
    absl::string_view response_code);

// Returns the HTTP/2 error code corresponding to the raw wire value, as defined
// in RFC 7540 Section 7. Unrecognized error codes are treated as INTERNAL_ERROR
// based on the RFC 7540 Section 7 suggestion.
Http2ErrorCode ToHttp2ErrorCode(uint32_t wire_error_code);

}  // namespace adapter
}  // namespace http2

#endif  // QUICHE_HTTP2_ADAPTER_NGHTTP2_UTIL_H_
