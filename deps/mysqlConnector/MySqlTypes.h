#pragma once

#include <map>
#include <string>

namespace Mysql
{
  enum class Option
  {
    OptConnectTimeout,           // uint32_t
    OptCompress,                 // bool
    OptNamedPipe,                // bool
    InitCommand,                 // string
    ReadDefaultFile,             // string
    ReadDefaultGroup,            // string
    SetCharsetDir,               // string
    SetCharsetName,              // string
    OptLocalInfile,              // bool
    OptProtocol,                 // uint32_t
    SharedMemoryBaseName,        // string
    OptReadTimeout,              // uint32_t
    OptWriteTimeout,             // uint32_t
    OptUseResult,                // special / legacy, no value (empty string recommended)
    OptUseRemoteConnection,      // bool, legacy
    OptUseEmbeddedConnection,    // bool, legacy
    OptGuessConnection,          // bool, legacy
    SetClientIp,                 // string, legacy
    SecureAuth,                  // bool, legacy
    ReportDataTruncation,        // bool
    OptReconnect,                // bool
    OptSslVerifyServerCert,      // bool, legacy
    PluginDir,                   // string
    DefaultAuth,                 // string
    OptBind,                     // string
    OptSslKey,                   // string
    OptSslCert,                  // string
    OptSslCa,                    // string
    OptSslCapath,                // string
    OptSslCipher,                // string
    OptSslCrl,                   // string
    OptSslCrlpath,               // string
    OptConnectAttrReset,         // special, no value (empty string recommended)
    OptConnectAttrAdd,           // special, "key=value"
    OptConnectAttrDelete,        // special, "key"
    ServerPublicKey,             // string
    EnableCleartextPlugin,       // bool
    OptCanHandleExpiredPasswords,// bool
    OptSslEnforce,               // bool, legacy
    OptMaxAllowedPacket,         // uint32_t
    OptNetBufferLength,          // uint32_t
    OptTlsVersion,               // string
    OptSslMode                   // special enum / MySQL-only, one of: disabled, preferred, required, verify_ca, verify_identity
  };

  using NativeConnectionHandle = void*;
  using NativeStatementHandle = void*;
  using NativeResultHandle = void*;
  using OptionMap = std::map< Option, std::string >;
}// namespace Mysql
