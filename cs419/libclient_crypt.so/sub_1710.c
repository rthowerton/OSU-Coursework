signed __int64 __usercall sub_1710@<rax>(signed __int128 a1@<rdx:rax>, __int64 a2@<rcx>, __int64 a3@<rdi>, time_t a4@<rsi>, __int64 a5@<r8>, int a6@<r9d>)
{
  int v6; // er14
  unsigned __int8 v7; // bl
  unsigned int v8; // er13
  unsigned int v9; // ebp
  __int64 v10; // rbx
  __int64 v11; // r15
  __int64 v12; // rax
  int v13; // er15
  unsigned int v15; // ecx
  unsigned int v16; // ST10_4
  unsigned int v17; // ST0C_4
  time_t v18; // rsi
  time_t v19; // r9
  time_t v20; // [rsp+0h] [rbp-88h]
  unsigned int v21; // [rsp+Ch] [rbp-7Ch]
  unsigned __int64 v22; // [rsp+20h] [rbp-68h]
  __int64 v23; // [rsp+28h] [rbp-60h]
  __int64 v24; // [rsp+30h] [rbp-58h]
  __int64 v25; // [rsp+38h] [rbp-50h]
  int v26; // [rsp+40h] [rbp-48h]
  unsigned __int64 v27; // [rsp+48h] [rbp-40h]

  v6 = a3;
  v7 = BYTE8(a1);
  v27 = __readfsqword(0x28u);
  v20 = a4;
  if ( !a6 )
  {
    a3 = 0LL;
    v16 = a5;
    v17 = a2;
    v18 = time(0LL);
    a5 = v16;
    a1 = -8608480567731124087LL * (signed __int128)v18;
    a2 = v17;
    v19 = *((_QWORD *)&a1 + 1) + v18;
    a4 = v18 >> 63;
    a6 = (v19 >> 4) - a4;
  }
  v8 = a6 + a5;
  v9 = a6 - a2;
  if ( a6 - (signed int)a2 > (unsigned int)(a6 + a5) )
    return 1LL;
  v21 = v7;
  while ( 1 )
  {
    v23 = 20LL;
    v24 = 0LL;
    v25 = 0LL;
    v26 = 0;
    v22 = (unsigned __int64)_byteswap_ulong(v9) << 32;
    v10 = EVP_MD_CTX_create(a3, a4, *((_QWORD *)&a1 + 1), a2, a5);
    if ( !v10 )
      return 0xFFFFFFFFLL;
    v11 = EVP_PKEY_new_mac_key(855LL, 0LL, v20, v21);
    if ( !v11 )
    {
      EVP_MD_CTX_destroy(v10);
      return 0xFFFFFFFFLL;
    }
    v12 = EVP_sha1(855LL, 0LL);
    EVP_DigestSignInit(v10, 0LL, v12, 0LL, v11);
    EVP_DigestUpdate(v10, &v22, 8LL);
    v23 = 0LL;
    a3 = v10;
    v13 = EVP_DigestSignFinal(v10, &v24, &v23);
    EVP_MD_CTX_destroy(v10);
    if ( v13 != 1 || v23 != 20 )
      return 0xFFFFFFFFLL;
    LODWORD(a1) = HIBYTE(v26) & 0xF;
    a4 = *((unsigned __int8 *)&v24 + (unsigned int)(a1 + 3));
    v15 = ((*((unsigned __int8 *)&v24 + (unsigned int)(a1 + 1)) << 16)
         + a4
         + (*((unsigned __int8 *)&v24 + (HIBYTE(v26) & 0xF)) << 24)
         + (*((unsigned __int8 *)&v24 + (unsigned int)(a1 + 2)) << 8)) & 0x7FFFFFFF;
    *((_QWORD *)&a1 + 1) = 1000000 * (v15 / 0xF4240);
    a2 = v15 % 0xF4240;
    if ( v6 == (_DWORD)a2 )
      break;
    if ( v8 < ++v9 )
      return 1LL;
  }
  return 0LL;
}