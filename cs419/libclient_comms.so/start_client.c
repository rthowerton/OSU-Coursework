__int64 __fastcall start_client(char *cp, __int16 a2)
{
  int v2; // edi
  unsigned int v3; // ebp
  unsigned __int64 v5; // rax
  __int64 *v6; // r13
  __int64 *v7; // rsi
  int v8; // eax
  char v9; // al
  __int64 *v10; // r13
  unsigned __int64 v11; // rax
  int v12; // eax
  __int64 *v13; // r13
  unsigned __int64 v14; // rax
  int v15; // eax
  unsigned __int64 v16; // rax
  __int64 *v17; // r14
  int v18; // eax
  int v19; // [rsp+4Ch] [rbp-EBCh]
  struct sockaddr addr; // [rsp+50h] [rbp-EB8h]
  int v21; // [rsp+60h] [rbp-EA8h]
  int v22; // [rsp+78h] [rbp-E90h]
  __int64 v23; // [rsp+80h] [rbp-E88h]
  __int64 v24; // [rsp+C0h] [rbp-E48h]
  __int64 v25; // [rsp+380h] [rbp-B88h]
  __int64 v26; // [rsp+388h] [rbp-B80h]
  __int64 v27; // [rsp+390h] [rbp-B78h]
  __int64 v28; // [rsp+398h] [rbp-B70h]
  __int64 v29; // [rsp+3A0h] [rbp-B68h]
  __int64 v30; // [rsp+3A8h] [rbp-B60h]
  __int64 v31; // [rsp+3B0h] [rbp-B58h]
  __int64 v32; // [rsp+3B8h] [rbp-B50h]
  __int128 v33; // [rsp+3C0h] [rbp-B48h]
  __int64 v34; // [rsp+3D0h] [rbp-B38h]
  __int128 v35; // [rsp+3D8h] [rbp-B30h]
  __int128 v36; // [rsp+3E8h] [rbp-B20h]
  __int64 v37; // [rsp+3F8h] [rbp-B10h]
  __int16 v38; // [rsp+400h] [rbp-B08h]
  unsigned __int64 v39; // [rsp+680h] [rbp-888h]
  unsigned __int64 v40; // [rsp+688h] [rbp-880h]
  int fd; // [rsp+690h] [rbp-878h]
  int v42; // [rsp+694h] [rbp-874h]
  char v43; // [rsp+6DCh] [rbp-82Ch]
  __int64 v44; // [rsp+7E0h] [rbp-728h]
  __int64 v45; // [rsp+7E8h] [rbp-720h]
  __int16 v46; // [rsp+7F0h] [rbp-718h]
  int v47; // [rsp+800h] [rbp-708h]
  __int16 v48; // [rsp+804h] [rbp-704h]
  char v49; // [rsp+806h] [rbp-702h]
  __int64 v50; // [rsp+810h] [rbp-6F8h]
  char v51; // [rsp+818h] [rbp-6F0h]
  __int128 v52; // [rsp+820h] [rbp-6E8h]
  __int64 v53; // [rsp+830h] [rbp-6D8h]
  __int64 v54; // [rsp+838h] [rbp-6D0h]
  __int128 v55; // [rsp+840h] [rbp-6C8h]
  __int64 v56; // [rsp+850h] [rbp-6B8h]
  __int64 v57; // [rsp+858h] [rbp-6B0h]
  char v58; // [rsp+860h] [rbp-6A8h]
  char v59; // [rsp+870h] [rbp-698h]
  __int64 v60; // [rsp+878h] [rbp-690h]
  __int64 v61; // [rsp+880h] [rbp-688h]
  __int64 v62; // [rsp+888h] [rbp-680h]
  __int64 v63; // [rsp+890h] [rbp-678h]
  __int64 v64; // [rsp+898h] [rbp-670h]
  __int64 v65; // [rsp+8A0h] [rbp-668h]
  __int64 v66; // [rsp+8A8h] [rbp-660h]
  char v67; // [rsp+8B0h] [rbp-658h]
  char v68[58]; // [rsp+8C0h] [rbp-648h]
  __int64 v69; // [rsp+8FAh] [rbp-60Eh]
  __int64 v70; // [rsp+902h] [rbp-606h]
  int v71; // [rsp+90Ah] [rbp-5FEh]
  __int16 v72; // [rsp+90Eh] [rbp-5FAh]
  char v73; // [rsp+910h] [rbp-5F8h]
  char v74; // [rsp+BC0h] [rbp-348h]
  unsigned __int64 v75; // [rsp+EC8h] [rbp-40h]

  *(_QWORD *)&addr.sa_data[6] = 0LL;
  v75 = __readfsqword(0x28u);
  addr.sa_family = 2;
  memset(&v21, 0, 0x790uLL);
  v21 = 1;
  *(_WORD *)addr.sa_data = __ROR2__(a2, 8);
  *(_DWORD *)&addr.sa_data[2] = inet_addr(cp);
  v2 = socket(2, 1, 0);
  fd = v2;
  v3 = 1;
  if ( v2 )
  {
    if ( connect(v2, &addr, 0x10u) < 0 )
    {
      v2 = fd;
    }
    else
    {
      do
      {
        memset(v68, 0, 0x300uLL);
        v50 = 0LL;
        v51 = 0;
        v47 = 0;
        v48 = 0;
        v49 = 0;
        memset(&v74, 0, 0x300uLL);
        memset(&v52, 0, 0x40uLL);
        v58 = 0;
        memset(&v59, 0, 0x40uLL);
        v46 = 0;
        v67 = 0;
        switch ( v21 )
        {
          case 1:
            v44 = 0LL;
            v19 = 16;
            v45 = 0LL;
            LOWORD(v44) = 2;
            if ( getsockname(fd, (struct sockaddr *)&v44, (socklen_t *)&v19) < 0 )
              goto LABEL_12;
            v21 = 2;
            v22 = HIDWORD(v44);
            v9 = v43;
            continue;
          case 2:
            v39 = 0LL;
            memset(&v23, 0, 0x300uLL);
            v40 = 0LL;
            LOBYTE(v19) = 2;
            memset(&v25, 0, 0x300uLL);
            if ( (unsigned int)enc_ki(&v74, 512LL) )
              goto LABEL_12;
            if ( (unsigned int)bcvh(&v19, 1LL, &v46, 3LL) )
              goto LABEL_12;
            if ( (unsigned int)bcvh(&v22, 4LL, &v50, 9LL) )
              goto LABEL_12;
            if ( (unsigned int)cid(&v22, &v42, &v47) )
              goto LABEL_12;
            if ( (unsigned int)bcvh(&v42, 32LL, &v52, 65LL) )
              goto LABEL_12;
            *(_OWORD *)&v68[10] = v52;
            *(_WORD *)v68 = v46;
            *(_QWORD *)&v68[2] = v50;
            *(_QWORD *)&v68[26] = v53;
            v71 = v47;
            *(_QWORD *)&v68[34] = v54;
            v72 = v48;
            *(_OWORD *)&v68[42] = v55;
            v69 = v56;
            v70 = v57;
            qmemcpy(&v73, &v74, 0x200uLL);
            if ( (unsigned int)c_hh(v68, 592LL, &v59, 64LL) )
              goto LABEL_12;
            v25 = *(_QWORD *)&v59;
            v26 = v60;
            v27 = v61;
            v28 = v62;
            v29 = v63;
            v30 = v64;
            v31 = v65;
            v32 = v66;
            qmemcpy(&v33, v68, 0x250uLL);
            if ( (unsigned int)sub_B30((__int64)&v21) )
              goto LABEL_12;
            v10 = &v23;
            v40 = 656LL;
            v39 = 0LL;
            memset(&v23, 0, 0x300uLL);
            v11 = 0LL;
            while ( 1 )
            {
              v12 = recv(fd, v10, 768 - v11, 0);
              if ( v12 < 0 )
                goto LABEL_12;
              v10 = (__int64 *)((char *)v10 + v12);
              v11 = v39 + v12;
              v39 = v11;
              if ( v11 > 0x2FF )
              {
                v39 = 64LL;
                if ( (unsigned int)v_hh(&v25, v40, &v23, 64LL) )
                  goto LABEL_12;
                v21 = 3;
                v9 = v43;
                goto LABEL_13;
              }
            }
          case 3:
            LOBYTE(v19) = 3;
            v39 = 0LL;
            memset(&v23, 0, 0x300uLL);
            v40 = 0LL;
            memset(&v25, 0, 0x300uLL);
            memset(v68, 0, 0x300uLL);
            if ( (unsigned int)bcvh(&v19, 1LL, &v46, 3LL) )
              goto LABEL_12;
            if ( (unsigned int)bcvh(&v42, 32LL, &v52, 65LL) )
              goto LABEL_12;
            *(_OWORD *)&v68[2] = v52;
            *(_WORD *)v68 = v46;
            *(_QWORD *)&v68[18] = v53;
            *(_QWORD *)&v68[26] = v54;
            *(_OWORD *)&v68[34] = v55;
            *(_QWORD *)&v68[50] = v56;
            v69 = v57;
            if ( (unsigned int)c_hh(v68, 66LL, &v59, 64LL) )
              goto LABEL_12;
            v13 = &v25;
            v25 = *(_QWORD *)&v59;
            v26 = v60;
            v27 = v61;
            v28 = v62;
            v29 = v63;
            v30 = v64;
            v31 = v65;
            v32 = v66;
            v33 = *(_OWORD *)v68;
            v14 = 0LL;
            v34 = *(_QWORD *)&v68[16];
            v35 = *(_OWORD *)&v68[24];
            v36 = *(_OWORD *)&v68[40];
            v37 = *(_QWORD *)&v68[56];
            v40 = 0LL;
            v38 = HIWORD(v69);
            while ( 1 )
            {
              v15 = send(fd, v13, 768 - v14, 0);
              if ( v15 < 0 )
                goto LABEL_12;
              v13 = (__int64 *)((char *)v13 + v15);
              v14 = v40 + v15;
              v40 = v14;
              if ( v14 > 0x2FF )
              {
                v16 = 0LL;
                v40 = 130LL;
                v39 = 0LL;
                v17 = &v23;
                memset(&v23, 0, 0x300uLL);
                while ( 1 )
                {
                  v18 = recv(fd, v17, 768 - v16, 0);
                  if ( v18 < 0 )
                    goto LABEL_12;
                  v17 = (__int64 *)((char *)v17 + v18);
                  v16 = v39 + v18;
                  v39 = v16;
                  if ( v16 > 0x2FF )
                  {
                    v39 = 106LL;
                    if ( !(unsigned int)v_hh(&v24, 42LL, &v23, 64LL) )
                    {
                      memset(&v59, 0, 0x40uLL);
                      if ( !(unsigned int)c_hh(&v23, v39, &v59, 64LL) )
                      {
                        v39 = 0LL;
                        v40 = 0LL;
                        memset(&v23, 0, 0x300uLL);
                        memset(&v25, 0, 0x300uLL);
                        v25 = *(_QWORD *)&v59;
                        v26 = v60;
                        v27 = v61;
                        v28 = v62;
                        v29 = v63;
                        v30 = v64;
                        v31 = v65;
                        v32 = v66;
                        if ( !(unsigned int)sub_B30((__int64)&v21) )
                        {
                          v40 = 64LL;
                          v21 = 4;
                          v9 = v43;
                          goto LABEL_13;
                        }
                      }
                    }
                    goto LABEL_12;
                  }
                }
              }
            }
          case 4:
            v5 = 0LL;
            v21 = 5;
            v39 = 0LL;
            v40 = 0LL;
            v6 = &v23;
            memset(&v25, 0, 0x300uLL);
            memset(&v23, 0, 0x300uLL);
            break;
          case 5:
            v39 = 0LL;
            v40 = 0LL;
            v43 = 1;
            memset(&v23, 0, 0x300uLL);
            memset(&v25, 0, 0x300uLL);
            goto LABEL_6;
          default:
            v39 = 0LL;
            v40 = 0LL;
            memset(&v23, 0, 0x300uLL);
            memset(&v25, 0, 0x300uLL);
            goto LABEL_30;
        }
        do
        {
          v7 = v6;
          v8 = recv(fd, v6, 768 - v5, 0);
          if ( v8 < 0 )
            goto LABEL_12;
          v6 = (__int64 *)((char *)v6 + v8);
          v5 = v39 + v8;
          v39 = v5;
        }
        while ( v5 <= 0x2FF );
        if ( (unsigned int)dispatch_server_command(&v21, v7) )
        {
LABEL_12:
          v9 = v43;
          v21 = 5;
          continue;
        }
LABEL_30:
        v9 = v43;
LABEL_13:
        ;
      }
      while ( !v9 );
LABEL_6:
      v2 = fd;
      v3 = 0;
    }
  }
  shutdown(v2, 2);
  return v3;
}