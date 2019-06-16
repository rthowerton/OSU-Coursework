signed __int64 __fastcall sub_1C90(__int64 a1, __int64 a2, _QWORD *a3, __int64 a4)
{
  _QWORD *v4; // rbp
  __int64 v5; // r13
  unsigned int v6; // er15
  __int64 v7; // rax
  unsigned int v9; // [rsp+8h] [rbp-A0h]
  int v10; // [rsp+Ch] [rbp-9Ch]
  __int64 v11; // [rsp+10h] [rbp-98h]
  __int64 v12; // [rsp+18h] [rbp-90h]
  __int64 v13; // [rsp+20h] [rbp-88h]
  __int64 v14; // [rsp+28h] [rbp-80h]
  char v15; // [rsp+30h] [rbp-78h]
  __int64 v16; // [rsp+40h] [rbp-68h]
  __int64 v17; // [rsp+48h] [rbp-60h]
  __int64 v18; // [rsp+50h] [rbp-58h]
  __int64 v19; // [rsp+58h] [rbp-50h]
  char v20; // [rsp+60h] [rbp-48h]
  unsigned __int64 v21; // [rsp+68h] [rbp-40h]

  v21 = __readfsqword(0x28u);
  v11 = 0LL;
  v12 = 0LL;
  v13 = 0LL;
  v14 = 0LL;
  v15 = 0;
  v9 = 0;
  v10 = 0;
  v16 = 0LL;
  v17 = 0LL;
  v18 = 0LL;
  v19 = 0LL;
  v20 = 0;
  if ( !a1 )
    return 1LL;
  v4 = a3;
  if ( !a3 )
    return 1LL;
  if ( !a2 )
    return 1LL;
  if ( a4 != 32 )
    return 1LL;
  sub_1930((__int64)&v16, 0x21uLL);
  v5 = base32_decode((__int64)&v16, (__int64)&v9);
  if ( !v5 )
    return 1LL;
  v6 = v9;
  v7 = EVP_sha256(&v16, &v9);
  if ( !HMAC(v7, v5, v6, a1, a2, &v11, &v10) || v10 != 32 )
    return 1LL;
  *v4 = v11;
  v4[1] = v12;
  v4[2] = v13;
  v4[3] = v14;
  return 0LL;
}