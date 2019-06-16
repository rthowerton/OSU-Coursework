_BOOL8 __fastcall v_hh(__int64 a1, __int64 a2, const void *a3, unsigned __int64 a4)
{
  const void *v4; // rbp
  _BOOL8 result; // rax
  __int64 v6; // [rsp+0h] [rbp-68h]
  char v7; // [rsp+40h] [rbp-28h]
  unsigned __int64 v8; // [rsp+48h] [rbp-20h]

  v4 = a3;
  v8 = __readfsqword(0x28u);
  memset(&v6, 0, 0x40uLL);
  v7 = 0;
  if ( a1 && a3 && a2 && a4 > 0x3F && !(unsigned int)c_hh() )
    result = memcmp(&v6, v4, 0x40uLL) != 0;
  else
    result = 1LL;
  return result;
}