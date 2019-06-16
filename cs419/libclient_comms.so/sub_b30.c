signed __int64 __fastcall sub_B30(__int64 a1)
{
  unsigned __int64 v1; // rax
  char *v2; // rbp
  int v3; // eax

  v1 = 0LL;
  v2 = (char *)(a1 + 800);
  *(_QWORD *)(a1 + 1576) = 0LL;
  do
  {
    v3 = send(*(_DWORD *)(a1 + 1584), v2, 768 - v1, 0);
    if ( v3 < 0 )
      return 1LL;
    v2 += v3;
    v1 = *(_QWORD *)(a1 + 1576) + v3;
    *(_QWORD *)(a1 + 1576) = v1;
  }
  while ( v1 <= 0x2FF );
  return 0LL;
}