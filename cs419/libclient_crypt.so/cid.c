__int64 __fastcall cid(unsigned int *a1, _QWORD *a2, __int64 a3)
{
  __int64 v3; // r13
  unsigned int v4; // ebp
  int v5; // er14
  __int64 v6; // rax
  __int64 v7; // r8
  void *v8; // rbx
  unsigned int v10; // er15
  __int64 v11; // rax
  int v12; // [rsp+4h] [rbp-C4h]
  unsigned int v13; // [rsp+8h] [rbp-C0h]
  unsigned int v14; // [rsp+Ch] [rbp-BCh]
  unsigned int v15; // [rsp+10h] [rbp-B8h]
  unsigned int v16; // [rsp+20h] [rbp-A8h]
  __int16 v17; // [rsp+24h] [rbp-A4h]
  char v18; // [rsp+26h] [rbp-A2h]
  unsigned __int64 v19; // [rsp+30h] [rbp-98h]
  __int16 v20; // [rsp+38h] [rbp-90h]
  __int64 v21; // [rsp+40h] [rbp-88h]
  __int64 v22; // [rsp+48h] [rbp-80h]
  __int64 v23; // [rsp+50h] [rbp-78h]
  __int64 v24; // [rsp+58h] [rbp-70h]
  __int64 v25; // [rsp+60h] [rbp-68h]
  __int64 v26; // [rsp+68h] [rbp-60h]
  __int64 v27; // [rsp+70h] [rbp-58h]
  __int64 v28; // [rsp+78h] [rbp-50h]
  char v29; // [rsp+80h] [rbp-48h]
  unsigned __int64 v30; // [rsp+88h] [rbp-40h]

  v3 = a3;
  v30 = __readfsqword(0x28u);
  v12 = 0;
  v15 = 0;
  v16 = 0;
  v17 = 0;
  v18 = 0;
  v21 = 0LL;
  v22 = 0LL;
  v23 = 0LL;
  v24 = 0LL;
  v13 = 0;
  v19 = 0LL;
  v20 = 0;
  v14 = 0;
  v25 = 0LL;
  v26 = 0LL;
  v27 = 0LL;
  v28 = 0LL;
  v29 = 0;
  if ( a1 )
    v15 = *a1;
  else
    gia(&v15);
  v4 = 1;
  v5 = epochtime();
  sub_1930(&v25, 33LL);
  v6 = base32_decode((__int64)&v25, (__int64)&v13);
  v8 = (void *)v6;
  if ( v6 )
  {
    if ( (unsigned int)get_totp_token(v6, v13, v5, &v14, v7) == 1
      && (unsigned int)__snprintf_chk(&v16, 7LL, 1LL, 7LL, "%06u", v14) == 6
      && (v10 = v13,
          v19 = __PAIR__(v16, v15),
          v20 = v17,
          v11 = EVP_sha256(&v16, 7LL),
          HMAC(v11, v8, v10, &v19, 10LL, &v21, &v12)) )
    {
      *a2 = v21;
      a2[1] = v22;
      a2[2] = v23;
      a2[3] = v24;
      *(_DWORD *)v3 = v16;
      v4 = 0;
      *(_WORD *)(v3 + 4) = v17;
    }
    else
    {
      v4 = 1;
    }
    free(v8);
  }
  return v4;
}