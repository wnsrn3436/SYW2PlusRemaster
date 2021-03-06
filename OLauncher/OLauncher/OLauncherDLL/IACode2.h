#pragma once

// https://elixir.bootlin.com/linux/latest/source/arch/x86/lib/x86-opcode-map.txt
typedef enum _IACODE2
{
	_00_GRP6,
	_01_GRP7,
	_02_LAR,
	_03_LSL,
	_04_UNKNOWN,
	_05_SYSCALL,
	_06_CLTS,
	_07_SYSRET,
	_08_INVD,
	_09_WBINVD,
	_0A_UNKNOWN,
	_0B_UD2,
	_0C_UNKNOWN,
	_0D_GRPP,
	_0E_FEMMS,
	_0F_3DNOW,
	_10_VMOVUPS,
	_11_VMOVUPS,
	_12_VMOVLPS,
	_13_VMOVLPS,
	_14_VUNPCKLPS,
	_15_VUNPCKHPS,
	_16_VMOVHPS,
	_17_VMOVHPS,
	_18_GRP16,
	_19_UNKNOWN,
	_1A_BNDCL,
	_1B_BNDCN,
	_1C_UNKNOWN,
	_1D_UNKNOWN,
	_1E_UNKNOWN,
	_1F_NOP,
	_20_MOV,
	_21_MOV,
	_22_MOV,
	_23_MOV,
	_24_UNKNOWN,
	_25_UNKNOWN,
	_26_UNKNOWN,
	_27_UNKNOWN,
	_28_VMOVAPS,
	_29_VMOVAPS,
	_2A_CVTPI2PS,
	_2B_VMOVNTPS,
	_2C_CVTTPS2PI,
	_2D_CVTPS2PI,
	_2E_VUCOMISS,
	_2F_VCOMISS,
	_30_WRMSR,
	_31_RDTSC,
	_32_RDMSR,
	_33_RDPMC,
	_34_SYSENTER,
	_35_SYSEXIT,
	_36_UNKNOWN,
	_37_GETSEC,
	_38_ESCAPE,
	_39_UNKNOWN,
	_3A_ESCAPE,
	_3B_UNKNOWN,
	_3C_UNKNOWN,
	_3D_UNKNOWN,
	_3E_UNKNOWN,
	_3F_UNKNOWN,
	_40_CMOVO,
	_41_CMOVNO,
	_42_CMOVB_C_NAE,
	_43_CMOVAE_NB_NC,
	_44_CMOVE_Z,
	_45_CMOVNE_NZ,
	_46_CMOVBE_NA,
	_47_CMOVA_NBE,
	_48_CMOVS,
	_49_CMOVNS,
	_4A_CMOVP_PE,
	_4B_CMOVNP_PO,
	_4C_CMOVL_NGE,
	_4D_CMOVNL_GE,
	_4E_CMOVLE_NG,
	_4F_CMOVNLE_G,
	_50_VMOVMSKPS,
	_51_VSQRTPS,
	_52_VRSQRTPS,
	_53_VRCPPS,
	_54_VANDPS,
	_55_VANDNPS,
	_56_VORPS,
	_57_VXORPS,
	_58_VADDPS,
	_59_VMULPS,
	_5A_VCVTPS2PD,
	_5B_VCVTDQ2PS,
	_5C_VSUBPS,
	_5D_VMINPS,
	_5E_VDIVPS,
	_5F_VMAXPS,
	_60_PUNPCKLBW,
	_61_PUNPCKLWD,
	_62_PUNPCKLDQ,
	_63_PACKSSWB,
	_64_PCMPGTB,
	_65_PCMPGTW,
	_66_PCMPGTD,
	_67_PACKUSWB,
	_68_PUNPCKHBW,
	_69_PUNPCKHWD,
	_6A_PUNPCKHDQ,
	_6B_PACKSSDW,
	_6C_VPUNPCKLQDQ,
	_6D_VPUNPCKHQDQ,
	_6E_MOVD_Q,
	_6F_MOVQ,
	_70_PSHUFW,
	_71_GRP12,
	_72_GRP13,
	_73_GRP14,
	_74_PCMPEQB,
	_75_PCMPEQW,
	_76_PCMPEQD,
	_77_EMMS,
	_78_VMREAD,
	_79_VMWRITE,
	_7A_VCVTUDQ2PD_UQQ2PD,
	_7B_VCVTUSI2SD,
	_7C_VHADDPD,
	_7D_VHSUBPD,
	_7E_MOVD_Q,
	_7F_MOVQ,
	_80_JO,
	_81_JNO,
	_82_JB_JC_JNAE,
	_83_JAE_JNB_JNC,
	_84_JE_JZ,
	_85_JNE_JNZ,
	_86_JBE_JNA,
	_87_JA_JNBE,
	_88_JS,
	_89_JNS,
	_8A_JP_JPE,
	_8B_JNP_JPO,
	_8C_JL_JNGE,
	_8D_JNL_JGE,
	_8E_JLE_JNG,
	_8F_JNLE_JG,
	_90_SETO,
	_91_SETNO,
	_92_SETB_C_NAE,
	_93_SETAE_NB_NC,
	_94_SETE_Z,
	_95_SETNE_NZ,
	_96_SETBE_NA,
	_97_SETA_NBE,
	_98_SETS,
	_99_SETNS,
	_9A_SETP_PE,
	_9B_SETNP_PO,
	_9C_SETL_NGE,
	_9D_SETNL_GE,
	_9E_SETLE_NG,
	_9F_SETNLE_G,
	_A0_PUSH,
	_A1_POP,
	_A2_CPUID,
	_A3_BT,
	_A4_SHLD,
	_A5_SHLD,
	_A6_GRPPDLK,
	_A7_GRPRNG,
	_A8_PUSH,
	_A9_POP,
	_AA_RSM,
	_AB_BTS,
	_AC_SHRD,
	_AD_SHRD,
	_AE_GRP15,
	_AF_IMUL,
	_B0_CMPXCHG,
	_B1_CMPXCHG,
	_B2_LSS,
	_B3_BTR,
	_B4_LFS,
	_B5_LGS,
	_B6_MOVZX,
	_B7_MOVZX,
	_B8_JMPE,
	_B9_GRP10,
	_BA_GRP8,
	_BB_BTC,
	_BC_BSF,
	_BD_BSR,
	_BE_MOVSX,
	_BF_MOVSX,
	_C0_XADD,
	_C1_XADD,
	_C2_VCMPPS,
	_C3_MOVNTI,
	_C4_PINSRW,
	_C5_PEXTRW,
	_C6_VSHUFPS,
	_C7_GRP9,
	_C8_BSWAP,
	_C9_BSWAP,
	_CA_BSWAP,
	_CB_BSWAP,
	_CC_BSWAP,
	_CD_BSWAP,
	_CE_BSWAP,
	_CF_BSWAP,
	_D0_VADDSUBPD,
	_D1_PSRLW,
	_D2_PSRLD,
	_D3_PSRLQ,
	_D4_PADDQ,
	_D5_PMULLW,
	_D6_VMOVQ,
	_D7_PMOVMSKB,
	_D8_PSUBUSB,
	_D9_PSUBUSW,
	_DA_PMINUB,
	_DB_PAND,
	_DC_PADDUSB,
	_DD_PADDUSW,
	_DE_PMAXUB,
	_DF_PANDN,
	_E0_PAVGB,
	_E1_PSRAW,
	_E2_PSRAD,
	_E3_PAVGW,
	_E4_PMULHUW,
	_E5_PMULHW,
	_E6_VCVTTPD2DQ,
	_E7_MOVNTQ,
	_E8_PSUBSB,
	_E9_PSUBSW,
	_EA_PMINSW,
	_EB_POR,
	_EC_PADDSB,
	_ED_PADDSW,
	_EE_PMAXSW,
	_EF_PXOR,
	_F0_VLDDQU,
	_F1_PSLLW,
	_F2_PSLLD,
	_F3_PSLLQ,
	_F4_PMULUDQ,
	_F5_PMADDWD,
	_F6_PSADBW,
	_F7_MASKMOVQ,
	_F8_PSUBB,
	_F9_PSUBW,
	_FA_PSUBD,
	_FB_PSUBQ,
	_FC_PADDB,
	_FD_PADDW,
	_FE_PADDD,
	_FF_UD0
} IACODE2;