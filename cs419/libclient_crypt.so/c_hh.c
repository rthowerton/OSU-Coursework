signed __int64 __fastcall c_hh(__int64 a1, __int64 a2, _QWORD *a3, unsigned __int64 a4)
{
  _QWORD *v4; // rbp
  __int64 v5; // r14
  unsigned int v6; // ST1C_4
  __int64 v7; // rax
  unsigned int v9; // [rsp+18h] [rbp-120h]
  int v10; // [rsp+1Ch] [rbp-11Ch]
  __int64 v11; // [rsp+20h] [rbp-118h]
  __int64 v12; // [rsp+28h] [rbp-110h]
  __int64 v13; // [rsp+30h] [rbp-108h]
  __int64 v14; // [rsp+38h] [rbp-100h]
  char v15; // [rsp+40h] [rbp-F8h]
  __int64 v16; // [rsp+50h] [rbp-E8h]
  __int64 v17; // [rsp+58h] [rbp-E0h]
  __int64 v18; // [rsp+60h] [rbp-D8h]
  __int64 v19; // [rsp+68h] [rbp-D0h]
  char v20; // [rsp+70h] [rbp-C8h]
  __int64 v21; // [rsp+80h] [rbp-B8h]
  __int64 v22; // [rsp+88h] [rbp-B0h]
  __int64 v23; // [rsp+90h] [rbp-A8h]
  __int64 v24; // [rsp+98h] [rbp-A0h]
  char v25; // [rsp+A0h] [rbp-98h]
  __int64 v26; // [rsp+B0h] [rbp-88h]
  __int64 v27; // [rsp+B8h] [rbp-80h]
  __int64 v28; // [rsp+C0h] [rbp-78h]
  __int64 v29; // [rsp+C8h] [rbp-70h]
  __int64 v30; // [rsp+D0h] [rbp-68h]
  __int64 v31; // [rsp+D8h] [rbp-60h]
  __int64 v32; // [rsp+E0h] [rbp-58h]
  __int64 v33; // [rsp+E8h] [rbp-50h]
  char v34; // [rsp+F0h] [rbp-48h]
  unsigned __int64 v35; // [rsp+F8h] [rbp-40h]

  v4 = a3;
  v11 = 0LL;
  v12 = 0LL;
  v35 = __readfsqword(0x28u);
  v13 = 0LL;
  memset(&v26, 0, 0x40uLL);
  v14 = 0LL;
  v15 = 0;
  v34 = 0;
  if ( !a1 )
    return 1LL;
  if ( !a3 )
    return 1LL;
  if ( !a2 )
    return 1LL;
  if ( a4 <= 0x3F )
    return 1LL;
  v16 = 0LL;
  v17 = 0LL;
  v18 = 0LL;
  v19 = 0LL;
  v20 = 0;
  v9 = 0;
  v10 = 0;
  v21 = 0LL;
  v22 = 0LL;
  v23 = 0LL;
  v24 = 0LL;
  v25 = 0;
  sub_1930(&v21, 33LL);
  v5 = base32_decode((__int64)&v21, (__int64)&v9);
  if ( !v5 )
    return 1LL;
  v6 = v9;
  v7 = EVP_sha256(&v21, &v9);
  if ( !HMAC(v7, v5, v6, a1, a2, &v16, &v10) )
    return 1LL;
  if ( v10 != 32 )
    return 1LL;
  v11 = v16;
  v12 = v17;
  v13 = v18;
  v14 = v19;
  if ( (unsigned int)bcvh(&v11, 32LL, &v26, 65LL) )
    return 1LL;
  *v4 = v26;
  v4[1] = v27;
  v4[2] = v28;
  v4[3] = v29;
  v4[4] = v30;
  v4[5] = v31;
  v4[6] = v32;
  v4[7] = v33;
  return 0LL;
}