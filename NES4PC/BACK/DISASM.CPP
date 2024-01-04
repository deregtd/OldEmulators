void __fastcall TStartFrm::DisassembleROM1Click(TObject *Sender)
{
	if (Mem.MapperNum > 0) { Application->MessageBox("DisASM Error!", "Only Mapper #0 ROMS Currently Supported!", MB_OK); return; }

	AnsiString dval[0x8000], dbeg[0x8000], dinst[0x8000], dpref[0x8000], dpost[0x8000];
	int JumpPoint = 0;
	int linetotal = 0;
	int tmploc, g, h;
	unsigned char tb, nb, nb2;
	AnsiString tbval, nbval, ChStr;

	for (int i=0x10000 - (Mem.PRGPages * 0x4000); i<0xFFFA; i+=bytes[*Mem.Main[i]])
	{
		tb = *Mem.Main[i]; nb = *Mem.Main[i+1]; nb2 = *Mem.Main[i+2];
		dpref[linetotal] = ""; dval[linetotal] = ""; dpost[linetotal] = "";
		dinst[linetotal] = Mn[instruc[tb]];
		dbeg[linetotal] = "     ";
		if (bytes[tb] == 2) { dval[linetotal] = IntToHex(nb,2); }
		else if (bytes[tb] == 3) { dval[linetotal] = IntToHex((nb2 << 8) + nb,4); }
        if ((tb) || (nb) || (nb2)) linetotal++;
	}
	linetotal = 0;

	for (int i=0x10000 - (Mem.PRGPages * 0x4000); i<0xFFFA; i+=bytes[*Mem.Main[i]])
	{
		tb = *Mem.Main[i]; nb = *Mem.Main[i+1]; nb2 = *Mem.Main[i+2];
 		switch (addressmode[tb]) {
			case ImmA:
				dpref[linetotal] = "#$";
				break;
			case Abs:
				dpref[linetotal] = "$";
				if (((nb + (nb2 << 8)) >= 0x2000) && ((nb + (nb2 << 8)) <= 0x2007))
				{
					dpref[linetotal] = "";
					dval[linetotal] = RegInfoLow[(nb + (nb2 << 8)) & 0xFF];
 				}
				if (((nb + (nb2 << 8)) >= 0x4000) && ((nb + (nb2 << 8)) <= 0x4017))
				{
					dpref[linetotal] = "";
					dval[linetotal] = RegInfoHigh[(nb + (nb2 << 8)) & 0xFF];
				}
				break;
			case Zp:
				dpref[linetotal] = "$";
				break;
			case Ind:
				dpref[linetotal] = "($";
				dpost[linetotal] = ")";
				break;
			case Absx:
				dpref[linetotal] = "$";
				if (((nb + (nb2 << 8)) >= 0x2000) && ((nb + (nb2 << 8)) <= 0x2007))
				{
					dpref[linetotal] = "";
					dval[linetotal] = RegInfoLow[(nb + (nb2 << 8)) & 0xFF];
 				}
				if (((nb + (nb2 << 8)) >= 0x4000) && ((nb + (nb2 << 8)) <= 0x4017))
				{
					dpref[linetotal] = "";
					dval[linetotal] = RegInfoHigh[(nb + (nb2 << 8)) & 0xFF];
				}
				dpost[linetotal] = ", X";
				break;
			case Absy:
				dpref[linetotal] = "$";
				if (((nb + (nb2 << 8)) >= 0x2000) && ((nb + (nb2 << 8)) <= 0x2007))
				{
					dpref[linetotal] = "";
					dval[linetotal] = RegInfoLow[(nb + (nb2 << 8)) & 0xFF];
 				}
				if (((nb + (nb2 << 8)) >= 0x4000) && ((nb + (nb2 << 8)) <= 0x4017))
				{
					dpref[linetotal] = "";
					dval[linetotal] = RegInfoHigh[(nb + (nb2 << 8)) & 0xFF];
				}
				dpost[linetotal] = ", Y";
				break;
			case Zpx:
				dpref[linetotal] = "$";
				dpost[linetotal] = ", X";
				break;
			case Zpy:
				dpref[linetotal] = "$";
				dpost[linetotal] = ", Y";
				break;
			case Idx:
				dpref[linetotal] = "($";
				dpost[linetotal] = ", X)";
				break;
			case Idy:
				dpref[linetotal] = "($";
				dpost[linetotal] = "), Y";
				break;
			case Rel:
				dpref[linetotal] = "P";
				tmploc = i + 2 + (char)nb;
				g = 0;
				for (h=0x10000 - (Mem.PRGPages * 0x4000); h<=tmploc; h+=bytes[*Mem.Main[h]])
				{
					if (h == tmploc)
					{
						if (dbeg[g] == "     ")
						{
							JumpPoint++;
							dbeg[g] = AnsiString("P") + AnsiString(JumpPoint) + AnsiString(":");
							if (dbeg[g].Length() < 5) dbeg[g] += " ";
							if (dbeg[g].Length() < 5) dbeg[g] += " ";
						}
						dval[linetotal] = AnsiString(JumpPoint);
					}
					if ((*Mem.Main[h]) || (*Mem.Main[h+1])) g++;
				}
				break;
			case Acc:
				dpref[linetotal] = "A";
				break;
		}

		if ((tb) || (nb))
			linetotal++;
	}

    char newline[1];
    newline[0] = 10;
	char * blank = "     ";
	if (SaveDialog1->Execute())
    {
		FILE * out = fopen(SaveDialog1->FileName.c_str(), "wt");

		for (int i=0;i<linetotal;i++)
		{
			fwrite(dbeg[i].c_str(), dbeg[i].Length(), 1, out);
			fwrite(dinst[i].c_str(), dinst[i].Length(), 1, out);
			fwrite(blank, 3, 1, out);
			fwrite(dpref[i].c_str(), dpref[i].Length(), 1, out);
			fwrite(dval[i].c_str(), dval[i].Length(), 1, out);
			fwrite(dpost[i].c_str(), dpost[i].Length(), 1, out);
			fwrite(&newline[0], 1, 1, out);
		}

		fclose(out);
    }
}
