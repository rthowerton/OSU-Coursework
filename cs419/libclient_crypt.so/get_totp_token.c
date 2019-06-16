signed __int64 __fastcall get_totp_token(__int64 a1, unsigned __int8 a2, int a3, unsigned int *a4, __int64 a5)
{
  unsigned int *v5; // r12
  __int64 v6; // rax
  __int64 v7; // r14
  __int64 v8; // rbx
  __int64 v9; // rax
  int v10; // ebx
  signed __int64 result; // rax
  unsigned __int64 v12; // [rsp+0h] [rbp-58h]
  __int64 v13; // [rsp+8h] [rbp-50h]
  __int64 v14; // [rsp+10h] [rbp-48h]
  __int64 v15; // [rsp+18h] [rbp-40h]
  int v16; // [rsp+20h] [rbp-38h]
  unsigned __int64 v17; // [rsp+28h] [rbp-30h]

  v5 = a4;
  v17 = __readfsqword(0x28u);
  v13 = 20LL;
  v14 = 0LL;
  v15 = 0LL;
  v16 = 0;
  v12 = (unsigned __int64)_byteswap_ulong(a3 / 30) << 32;
  v6 = EVP_MD_CTX_create(a1, (unsigned int)(a3 >> 31), v12, a4, a5);
  if ( !v6 )
    return 0LL;
  v7 = v6;
  v8 = EVP_PKEY_new_mac_key(855LL, 0LL, a1, a2);
  if ( !v8 )
  {
    EVP_MD_CTX_destroy(v7);
    return 0LL;
  }
  v9 = EVP_sha1();
  EVP_DigestSignInit(v7, 0LL, v9, 0LL, v8);
  EVP_DigestUpdate(v7, &v12, 8LL);
  v13 = 0LL;
  v10 = EVP_DigestSignFinal(v7, &v14, &v13);
  EVP_MD_CTX_destroy(v7);
  if ( v10 != 1 || v13 != 20 )
    return 0LL;
  result = 1LL;
  *v5 = (((*((unsigned __int8 *)&v14 + (HIBYTE(v16) & 0xFu) + 1) << 16)
        + *((unsigned __int8 *)&v14 + (HIBYTE(v16) & 0xFu) + 3)
        + (*((unsigned __int8 *)&v14 + (HIBYTE(v16) & 0xF)) << 24)
        + (*((unsigned __int8 *)&v14 + (HIBYTE(v16) & 0xFu) + 2) << 8)) & 0x7FFFFFFFu)
      % 0xF4240;
  return result;
}