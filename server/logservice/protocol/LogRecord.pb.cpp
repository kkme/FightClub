// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "LogRecord.pb.hpp"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace PWRD {

void protobuf_ShutdownFile_LogRecord_2eproto() {
  delete LogRecord::default_instance_;
}

void protobuf_AddDesc_LogRecord_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  LogRecord::default_instance_ = new LogRecord();
  LogRecord::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_LogRecord_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_LogRecord_2eproto {
  StaticDescriptorInitializer_LogRecord_2eproto() {
    protobuf_AddDesc_LogRecord_2eproto();
  }
} static_descriptor_initializer_LogRecord_2eproto_;

bool TYPE_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int LogRecord::kSequnceFieldNumber;
const int LogRecord::kTypeFieldNumber;
const int LogRecord::kServerFieldNumber;
const int LogRecord::kProcessFieldNumber;
const int LogRecord::kMessageFieldNumber;
#endif  // !_MSC_VER

LogRecord::LogRecord()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void LogRecord::InitAsDefaultInstance() {
}

LogRecord::LogRecord(const LogRecord& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void LogRecord::SharedCtor() {
  _cached_size_ = 0;
  sequnce_ = GOOGLE_LONGLONG(0);
  type_ = 0;
  server_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  process_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LogRecord::~LogRecord() {
  SharedDtor();
}

void LogRecord::SharedDtor() {
  if (server_ != &::google::protobuf::internal::kEmptyString) {
    delete server_;
  }
  if (process_ != &::google::protobuf::internal::kEmptyString) {
    delete process_;
  }
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    delete message_;
  }
  if (this != default_instance_) {
  }
}

void LogRecord::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const LogRecord& LogRecord::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_LogRecord_2eproto();  return *default_instance_;
}

LogRecord* LogRecord::default_instance_ = NULL;

LogRecord* LogRecord::New() const {
  return new LogRecord;
}

void LogRecord::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    sequnce_ = GOOGLE_LONGLONG(0);
    type_ = 0;
    if (has_server()) {
      if (server_ != &::google::protobuf::internal::kEmptyString) {
        server_->clear();
      }
    }
    if (has_process()) {
      if (process_ != &::google::protobuf::internal::kEmptyString) {
        process_->clear();
      }
    }
    if (has_message()) {
      if (message_ != &::google::protobuf::internal::kEmptyString) {
        message_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool LogRecord::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 sequnce = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &sequnce_)));
          set_has_sequnce();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_type;
        break;
      }
      
      // required int32 type = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_server;
        break;
      }
      
      // required string server = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_server:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_server()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_process;
        break;
      }
      
      // required string process = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_process:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_process()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_message;
        break;
      }
      
      // required string message = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_message:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_message()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LogRecord::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int64 sequnce = 1;
  if (has_sequnce()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->sequnce(), output);
  }
  
  // required int32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->type(), output);
  }
  
  // required string server = 3;
  if (has_server()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->server(), output);
  }
  
  // required string process = 4;
  if (has_process()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->process(), output);
  }
  
  // required string message = 5;
  if (has_message()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->message(), output);
  }
  
}

int LogRecord::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int64 sequnce = 1;
    if (has_sequnce()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->sequnce());
    }
    
    // required int32 type = 2;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }
    
    // required string server = 3;
    if (has_server()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->server());
    }
    
    // required string process = 4;
    if (has_process()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->process());
    }
    
    // required string message = 5;
    if (has_message()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->message());
    }
    
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LogRecord::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const LogRecord*>(&from));
}

void LogRecord::MergeFrom(const LogRecord& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_sequnce()) {
      set_sequnce(from.sequnce());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_server()) {
      set_server(from.server());
    }
    if (from.has_process()) {
      set_process(from.process());
    }
    if (from.has_message()) {
      set_message(from.message());
    }
  }
}

void LogRecord::CopyFrom(const LogRecord& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LogRecord::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001e) != 0x0000001e) return false;
  
  return true;
}

void LogRecord::Swap(LogRecord* other) {
  if (other != this) {
    std::swap(sequnce_, other->sequnce_);
    std::swap(type_, other->type_);
    std::swap(server_, other->server_);
    std::swap(process_, other->process_);
    std::swap(message_, other->message_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string LogRecord::GetTypeName() const {
  return "PWRD.LogRecord";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PWRD

// @@protoc_insertion_point(global_scope)