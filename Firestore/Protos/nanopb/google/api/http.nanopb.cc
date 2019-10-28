/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.2 */

#include "http.nanopb.h"

#include "absl/strings/str_cat.h"
#include "nanopb_pretty_printers.h"
namespace firebase {
namespace firestore {
/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t google_api_Http_fields[3] = {
    PB_FIELD(  1, MESSAGE , REPEATED, POINTER , FIRST, google_api_Http, rules, rules, &google_api_HttpRule_fields),
    PB_FIELD(  2, BOOL    , SINGULAR, STATIC  , OTHER, google_api_Http, fully_decode_reserved_expansion, rules, 0),
    PB_LAST_FIELD
};

const pb_field_t google_api_HttpRule_fields[10] = {
    PB_FIELD(  1, BYTES   , SINGULAR, POINTER , FIRST, google_api_HttpRule, selector, selector, 0),
    PB_ANONYMOUS_ONEOF_FIELD(pattern,   2, BYTES   , ONEOF, POINTER , OTHER, google_api_HttpRule, get, selector, 0),
    PB_ANONYMOUS_ONEOF_FIELD(pattern,   3, BYTES   , ONEOF, POINTER , UNION, google_api_HttpRule, put, selector, 0),
    PB_ANONYMOUS_ONEOF_FIELD(pattern,   4, BYTES   , ONEOF, POINTER , UNION, google_api_HttpRule, post, selector, 0),
    PB_ANONYMOUS_ONEOF_FIELD(pattern,   5, BYTES   , ONEOF, POINTER , UNION, google_api_HttpRule, delete_, selector, 0),
    PB_ANONYMOUS_ONEOF_FIELD(pattern,   6, BYTES   , ONEOF, POINTER , UNION, google_api_HttpRule, patch, selector, 0),
    PB_ANONYMOUS_ONEOF_FIELD(pattern,   8, MESSAGE , ONEOF, STATIC  , UNION, google_api_HttpRule, custom, selector, &google_api_CustomHttpPattern_fields),
    PB_FIELD(  7, BYTES   , SINGULAR, POINTER , OTHER, google_api_HttpRule, body, custom, 0),
    PB_FIELD( 11, MESSAGE , REPEATED, POINTER , OTHER, google_api_HttpRule, additional_bindings, body, &google_api_HttpRule_fields),
    PB_LAST_FIELD
};

const pb_field_t google_api_CustomHttpPattern_fields[3] = {
    PB_FIELD(  1, BYTES   , SINGULAR, POINTER , FIRST, google_api_CustomHttpPattern, kind, kind, 0),
    PB_FIELD(  2, BYTES   , SINGULAR, POINTER , OTHER, google_api_CustomHttpPattern, path, kind, 0),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(google_api_HttpRule, custom) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_google_api_Http_google_api_HttpRule_google_api_CustomHttpPattern)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(google_api_HttpRule, custom) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_google_api_Http_google_api_HttpRule_google_api_CustomHttpPattern)
#endif



  std::string Http::ToString(int indent) const {
      std::string result;

      bool is_root = indent == 0;
      std::string header;
      if (is_root) {
          indent = 1;
          auto p = absl::Hex{reinterpret_cast<uintptr_t>(this)};
          absl::StrAppend(&header, "<Http 0x", p, ">: {\n");
      } else {
          header = "{\n";
      }

        for (pb_size_t i = 0; i != rules_count; ++i) {
            result += PrintField("rules ", rules[i], indent + 1, true);
        }
        result += PrintField("fully_decode_reserved_expansion: ", fully_decode_reserved_expansion, indent + 1, false);

      if (!result.empty() || is_root) {
        std::string tail = Indent(is_root ? 0 : indent) + '}';
        return header + result + tail;
      } else {
        return "";
      }
  }

  std::string HttpRule::ToString(int indent) const {
      std::string result;

      bool is_root = indent == 0;
      std::string header;
      if (is_root) {
          indent = 1;
          auto p = absl::Hex{reinterpret_cast<uintptr_t>(this)};
          absl::StrAppend(&header, "<HttpRule 0x", p, ">: {\n");
      } else {
          header = "{\n";
      }

        result += PrintField("selector: ", selector, indent + 1, false);
        switch (which_pattern) {
          case 2: // google_api_HttpRule_get_tag
            result += PrintField("get: ", get, indent + 1, true);
            break;
          case 3: // google_api_HttpRule_put_tag
            result += PrintField("put: ", put, indent + 1, true);
            break;
          case 4: // google_api_HttpRule_post_tag
            result += PrintField("post: ", post, indent + 1, true);
            break;
          case 5: // google_api_HttpRule_delete_tag
            result += PrintField("delete_: ", delete_, indent + 1, true);
            break;
          case 6: // google_api_HttpRule_patch_tag
            result += PrintField("patch: ", patch, indent + 1, true);
            break;
          case 8: // google_api_HttpRule_custom_tag
            result += PrintField("custom ", custom, indent + 1, true);
            break;
        }

        result += PrintField("body: ", body, indent + 1, false);
        for (pb_size_t i = 0; i != additional_bindings_count; ++i) {
            result += PrintField("additional_bindings ", additional_bindings[i], indent + 1, true);
        }

      if (!result.empty() || is_root) {
        std::string tail = Indent(is_root ? 0 : indent) + '}';
        return header + result + tail;
      } else {
        return "";
      }
  }

  std::string CustomHttpPattern::ToString(int indent) const {
      std::string result;

      bool is_root = indent == 0;
      std::string header;
      if (is_root) {
          indent = 1;
          auto p = absl::Hex{reinterpret_cast<uintptr_t>(this)};
          absl::StrAppend(&header, "<CustomHttpPattern 0x", p, ">: {\n");
      } else {
          header = "{\n";
      }

        result += PrintField("kind: ", kind, indent + 1, false);
        result += PrintField("path: ", path, indent + 1, false);

      if (!result.empty() || is_root) {
        std::string tail = Indent(is_root ? 0 : indent) + '}';
        return header + result + tail;
      } else {
        return "";
      }
  }

}  // namespace firestore
}  // namespace firebase
/* @@protoc_insertion_point(eof) */
