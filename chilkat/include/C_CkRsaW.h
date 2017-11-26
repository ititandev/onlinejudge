// This is a generated source file for Chilkat version 9.5.0.69
#ifndef _C_CkRsaWH
#define _C_CkRsaWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC HCkRsaW CkRsaW_Create(void);
CK_VISIBLE_PUBLIC void CkRsaW_Dispose(HCkRsaW handle);
CK_VISIBLE_PUBLIC void CkRsaW_getCharset(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkRsaW_putCharset(HCkRsaW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_charset(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void CkRsaW_getDebugLogFilePath(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkRsaW_putDebugLogFilePath(HCkRsaW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_debugLogFilePath(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void CkRsaW_getEncodingMode(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkRsaW_putEncodingMode(HCkRsaW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_encodingMode(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void CkRsaW_getLastErrorHtml(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_lastErrorHtml(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void CkRsaW_getLastErrorText(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_lastErrorText(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void CkRsaW_getLastErrorXml(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_lastErrorXml(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC BOOL CkRsaW_getLastMethodSuccess(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void  CkRsaW_putLastMethodSuccess(HCkRsaW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkRsaW_getLittleEndian(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void  CkRsaW_putLittleEndian(HCkRsaW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkRsaW_getNoUnpad(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void  CkRsaW_putNoUnpad(HCkRsaW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkRsaW_getNumBits(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void CkRsaW_getOaepHash(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void  CkRsaW_putOaepHash(HCkRsaW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_oaepHash(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC BOOL CkRsaW_getOaepPadding(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void  CkRsaW_putOaepPadding(HCkRsaW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkRsaW_getVerboseLogging(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC void  CkRsaW_putVerboseLogging(HCkRsaW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkRsaW_getVersion(HCkRsaW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_version(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC BOOL CkRsaW_DecryptBytes(HCkRsaW cHandle, HCkByteData inData, BOOL usePrivateKey, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkRsaW_DecryptBytesENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkRsaW_DecryptString(HCkRsaW cHandle, HCkByteData binarySig, BOOL usePrivateKey, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_decryptString(HCkRsaW cHandle, HCkByteData binarySig, BOOL usePrivateKey);
CK_VISIBLE_PUBLIC BOOL CkRsaW_DecryptStringENC(HCkRsaW cHandle, const wchar_t *encodedSig, BOOL usePrivateKey, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_decryptStringENC(HCkRsaW cHandle, const wchar_t *encodedSig, BOOL usePrivateKey);
CK_VISIBLE_PUBLIC BOOL CkRsaW_EncryptBytes(HCkRsaW cHandle, HCkByteData binaryData, BOOL usePrivateKey, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkRsaW_EncryptBytesENC(HCkRsaW cHandle, HCkByteData data, BOOL bUsePrivateKey, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_encryptBytesENC(HCkRsaW cHandle, HCkByteData data, BOOL bUsePrivateKey);
CK_VISIBLE_PUBLIC BOOL CkRsaW_EncryptString(HCkRsaW cHandle, const wchar_t *stringToEncrypt, BOOL usePrivateKey, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkRsaW_EncryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_encryptStringENC(HCkRsaW cHandle, const wchar_t *str, BOOL bUsePrivateKey);
CK_VISIBLE_PUBLIC BOOL CkRsaW_ExportPrivateKey(HCkRsaW cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_exportPrivateKey(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC HCkPrivateKeyW CkRsaW_ExportPrivateKeyObj(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC BOOL CkRsaW_ExportPublicKey(HCkRsaW cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_exportPublicKey(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC HCkPublicKeyW CkRsaW_ExportPublicKeyObj(HCkRsaW cHandle);
CK_VISIBLE_PUBLIC BOOL CkRsaW_GenerateKey(HCkRsaW cHandle, int numBits);
CK_VISIBLE_PUBLIC BOOL CkRsaW_ImportPrivateKey(HCkRsaW cHandle, const wchar_t *xmlKey);
CK_VISIBLE_PUBLIC BOOL CkRsaW_ImportPrivateKeyObj(HCkRsaW cHandle, HCkPrivateKeyW key);
CK_VISIBLE_PUBLIC BOOL CkRsaW_ImportPublicKey(HCkRsaW cHandle, const wchar_t *xmlKey);
CK_VISIBLE_PUBLIC BOOL CkRsaW_ImportPublicKeyObj(HCkRsaW cHandle, HCkPublicKeyW key);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslSignBytes(HCkRsaW cHandle, HCkByteData data, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslSignBytesENC(HCkRsaW cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_openSslSignBytesENC(HCkRsaW cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslSignString(HCkRsaW cHandle, const wchar_t *str, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslSignStringENC(HCkRsaW cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_openSslSignStringENC(HCkRsaW cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslVerifyBytes(HCkRsaW cHandle, HCkByteData signature, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslVerifyBytesENC(HCkRsaW cHandle, const wchar_t *str, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslVerifyString(HCkRsaW cHandle, HCkByteData data, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_openSslVerifyString(HCkRsaW cHandle, HCkByteData data);
CK_VISIBLE_PUBLIC BOOL CkRsaW_OpenSslVerifyStringENC(HCkRsaW cHandle, const wchar_t *str, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_openSslVerifyStringENC(HCkRsaW cHandle, const wchar_t *str);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SaveLastError(HCkRsaW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SignBytes(HCkRsaW cHandle, HCkByteData binaryData, const wchar_t *hashAlgorithm, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SignBytesENC(HCkRsaW cHandle, HCkByteData binaryData, const wchar_t *hashAlgorithm, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_signBytesENC(HCkRsaW cHandle, HCkByteData binaryData, const wchar_t *hashAlgorithm);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SignHash(HCkRsaW cHandle, HCkByteData hashBytes, const wchar_t *hashAlg, HCkByteData outBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SignHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_signHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SignString(HCkRsaW cHandle, const wchar_t *strToBeHashed, const wchar_t *hashAlgorithm, HCkByteData outData);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SignStringENC(HCkRsaW cHandle, const wchar_t *strToBeHashed, const wchar_t *hashAlgorithm, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_signStringENC(HCkRsaW cHandle, const wchar_t *strToBeHashed, const wchar_t *hashAlgorithm);
CK_VISIBLE_PUBLIC BOOL CkRsaW_SnkToXml(HCkRsaW cHandle, const wchar_t *filename, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkRsaW_snkToXml(HCkRsaW cHandle, const wchar_t *filename);
CK_VISIBLE_PUBLIC BOOL CkRsaW_UnlockComponent(HCkRsaW cHandle, const wchar_t *unlockCode);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyBytes(HCkRsaW cHandle, HCkByteData originalData, const wchar_t *hashAlgorithm, HCkByteData signatureBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyBytesENC(HCkRsaW cHandle, HCkByteData originalData, const wchar_t *hashAlgorithm, const wchar_t *encodedSig);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyHash(HCkRsaW cHandle, HCkByteData hashBytes, const wchar_t *hashAlg, HCkByteData sigBytes);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyHashENC(HCkRsaW cHandle, const wchar_t *encodedHash, const wchar_t *hashAlg, const wchar_t *encodedSig);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyPrivateKey(HCkRsaW cHandle, const wchar_t *xml);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyString(HCkRsaW cHandle, const wchar_t *originalString, const wchar_t *hashAlgorithm, HCkByteData binarySig);
CK_VISIBLE_PUBLIC BOOL CkRsaW_VerifyStringENC(HCkRsaW cHandle, const wchar_t *originalString, const wchar_t *hashAlgorithm, const wchar_t *encodedSig);
#endif
