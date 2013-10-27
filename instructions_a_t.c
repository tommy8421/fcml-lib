/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_a_t.h"

int fcml_tf_instructions_a_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_a_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_AAA(void) {
	FCML_I32( "aaa", 0x37 );
}

void fcml_tf_instruction_AAD(void) {
	FCML_I32( "aad", 0xD5, 0x0A );
	FCML_I64_FAILED( "aad", 0xD5, 0x0A );
	FCML_I32( "aad 0ch", 0xD5, 0x0C );
	FCML_I64_FAILED( "aad 0ch", 0xD5, 0x0C );
}

void fcml_tf_instruction_AAM(void) {
	FCML_I32( "aam", 0xD4, 0x0A );
	FCML_I64_FAILED( "aam", 0xD4, 0x0A );
	FCML_I32( "aam 0ch", 0xD4, 0x0C );
	FCML_I64_FAILED( "aam 0ch", 0xD4, 0x0C );
}

void fcml_tf_instruction_AAS(void) {
	FCML_I32( "aas", 0x3F );
	FCML_I64_FAILED( "aas", 0x3F );
}

void fcml_tf_instruction_ADC(void) {
	// 14 ib ADC AL, imm8
	FCML_I32_FAILED( "lock adc al,42h", 0xF0, 0x14, 0x42 );
	FCML_I3264_M( "adc al,42h", 2, FCML_MI( 0x14, 0x42 ), FCML_MI( 0x80, 0xD0, 0x42 ) );
	FCML_I3264_M( "adc al,0ffh", 2, FCML_MI( 0x14, 0xFF ), FCML_MI( 0x80, 0xD0, 0xFF ) );
	FCML_I3264_M( "adc al,00h", 2, FCML_MI( 0x14, 0x00 ), FCML_MI( 0x80, 0xD0, 0x00 ) );
	// 15 iw ADC AX, imm16s
	// 15 id ADC EAX, imm32
	FCML_I3264_M( "adc ax,8042h", 2, FCML_MI( 0x66, 0x15, 0x42, 0x80 ), FCML_MI( 0x66, 0x81, 0xd0, 0x42, 0x80 ) );
	FCML_I32_FAILED( "lock adc ax,8042h", 0xF0, 0x66, 0x15, 0x42, 0x80 );
	FCML_I3264_M( "adc eax,42806521h", 2, FCML_MI( 0x15, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x81, 0xd0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_D( "adc eax,42806521h", 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc ax,6521h", 0x66, 0x40, 0x15, 0x21, 0x65 );
	// REX.W + 15 id ADC RAX, imm32
	FCML_I64_M( "adc rax,0000000042806521h", 2, FCML_MI( 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x48, 0x81, 0xd0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_D( "adc rax,0000000042806521h", 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc rax,0000000042806521h", 0x67, 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x15, 0xff, 0xff, 0xff, 0xff );
	// 80 /2 ib ADC r/m8, imm8
	// REX + 80 /2 ib ADC r/m8
	FCML_I32( "adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "lock adc byte ptr [04030201h],0ffh", 0xF0, 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "adc byte ptr [esi+04030201h],0ffh", 0x80, 0x96, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "adc byte ptr [ecx+eax+00000002h],03h", 0x80, 0x54, 0x01, 0x02, 0x03 );

	// 81 /2 iw ADC r/m16, imm16
	// 81 /2 id ADC r/m32, imm32
	FCML_I3264( "adc ebp,04030201h", 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32_A_FAILED( "lock adc ebp,04030201h", 0xF0, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I3264( "adc bp,0201h", 0x66, 0x81, 0xD5, 0x01, 0x02 );
	FCML_I64_D( "adc bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xD5, 0x01, 0x02 );
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	FCML_I64( "adc rbp,0000000004030201h", 0x48, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64_A_FAILED( "lock adc rbp,0000000004030201h", 0xF0, 0x48, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64_M( "adc rbp,0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x48, 0x83, 0xd5, 0xff ) );
	FCML_I64_D( "adc rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "adc rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	FCML_I32_M( "lock adc dword ptr [esi],00000001h", 2, FCML_MI( 0xF0, 0x83, 0x16, 0x01 ), FCML_MI( 0xF0, 0x81, 0x16, 0x01, 0x00, 0x00, 0x00 ) );
	FCML_I32_M( "adc word ptr [esi],0001h", 2, FCML_MI( 0x66, 0x83, 0x16, 0x01 ), FCML_MI( 0x66, 0x81, 0x16, 0x01, 0x00 ) );
	FCML_I64_M( "adc word ptr [rsi],0001h", 2, FCML_MI( 0x66, 0x83, 0x16, 0x01 ), FCML_MI( 0x66, 0x81, 0x16, 0x01, 0x00 ) );
	FCML_I32_M( "adc dword ptr [0201h],00000003h", 2, FCML_MI( 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 ), FCML_MI( 0x67, 0x81, 0x16, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00 ) );
	FCML_I32_M( "adc word ptr [0201h],0ffffh", 2, FCML_MI( 0x66, 0x67, 0x83, 0x16, 0x01, 0x02, 0xFF ), FCML_MI( 0x66, 0x67, 0x81, 0x16, 0x01, 0x02, 0xff, 0xff ) );
	FCML_I32_M( "adc dword ptr [0201h],00000003h", 2, FCML_MI( 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 ), FCML_MI( 0x67, 0x81, 0x16, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00 ) );
	// TODO: Sprawdzic 2 tryb adresowania ktory sie assembluje.
	FCML_I64_RIP_M( "adc dword ptr [0000800000401007h],00000003h", 2, FCML_MI( 0x83, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 ), FCML_MI( 0x81, 0x15, 0xfd, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00 ) );
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	FCML_I64_M( "adc qword ptr [rdi+0000000004030201h],0000000000000005h", 2, FCML_MI( 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0x05 ), FCML_MI( 0x48, 0x81, 0x97, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00 ) );
	FCML_I64_M( "adc qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0xff ), FCML_MI( 0x48, 0x81, 0x97, 0x01, 0x02, 0x03, 0x04, 0xff, 0xff, 0xff, 0xff ) );
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	FCML_I32( "lock adc byte ptr [ebp+04030201h],ah", 0xF0, 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "adc byte ptr [rbp+0000000000000001h],ah", 0x10, 0x65, 0x01 );
	FCML_I64( "adc byte ptr [rbp+0000000000000001h],spl", 0x40, 0x10, 0x65, 0x01 );
	FCML_I64( "adc byte ptr [rbp+0000000000000001h],r12l", 0x44, 0x10, 0x65, 0x01 );
	FCML_I64_D( "adc byte ptr [rbp+0000000000000001h],spl", 0x48, 0x10, 0x64, 0xa5, 0x01 );
	FCML_I64_D( "adc byte ptr [rbp+0000000000000001h],spl", 0x40, 0x10, 0x64, 0xa5, 0x01 );
	FCML_I64_D( "adc byte ptr [rbp+0000000000000001h],ah", 0x10, 0x64, 0xa5, 0x01 );
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	FCML_I32( "lock adc dword ptr [ebp+04030201h],esp", 0xF0, 0x11, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "adc word ptr [di+0201h],sp", 0x66, 0x67, 0x11, 0xa5, 0x01, 0x02 );
	FCML_I32( "adc dword ptr [di+0201h],esp", 0x67, 0x11, 0xa5, 0x01, 0x02 );
	FCML_I64( "adc qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x11, 0x64, 0x89, 0x01 );
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	FCML_I32( "adc ah,byte ptr [ebp+04030201h]", 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32_FAILED( "lock adc ah,byte ptr [ebp+04030201h]", 0xF0, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64_D( "adc spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64_D( "adc spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x12, 0x64, 0xa5, 0x01 );
	FCML_I64_D( "adc ah,byte ptr [rbp+0000000000000001h]", 0x12, 0x64, 0xa5, 0x01 );
	FCML_I64( "adc spl,byte ptr [rbp+0000000004030201h]", 0x40, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "adc spl,byte ptr [rbp+0000000000000001h]", 0x40, 0x12, 0x65, 0x01 );
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	FCML_I32( "adc esp,dword ptr [ebp+04030201h]", 0x13, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32_FAILED( "lock adc esp,dword ptr [ebp+04030201h]", 0xF0, 0x13, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "adc sp,word ptr [di+0201h]", 0x66, 0x67, 0x13, 0xa5, 0x01, 0x02 );
	FCML_I32( "adc esp,dword ptr [di+0201h]", 0x67, 0x13, 0xa5, 0x01, 0x02 );
	FCML_I64( "adc r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x13, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_ADD(void) {
	// 04 ib ADD AL, imm8 C Valid Valid Add imm8 to AL..
	FCML_I32_M( "add al,42h", 2, FCML_MI( 0x04, 0x42 ), FCML_MI( 0x80, 0xc0, 0x42 ) );
	FCML_I32_D_FAILED( "lock add al,42h", 0xF0, 0x04, 0x42 );
	FCML_I32_A_FAILED( "lock add al,42h", 0xF0, 0x04, 0x42 );
	FCML_I32_M( "add al,0ffh", 2, FCML_MI( 0x04, 0xff ), FCML_MI( 0x80, 0xc0, 0xff ) );
	FCML_I64_M( "add al,42h", 2, FCML_MI( 0x04, 0x42 ), FCML_MI( 0x80, 0xc0, 0x42 ) );
	FCML_I64_M( "add al,00h", 2, FCML_MI( 0x04, 0x00 ), FCML_MI( 0x80, 0xc0, 0x00 ) );
	FCML_I64_M( "add al,0ffh", 2, FCML_MI( 0x04, 0xff ), FCML_MI( 0x80, 0xc0, 0xff ) );
	// 05 iw ADD AX, imm16 C Valid Valid Add imm16 to AX.
	// 05 id ADD EAX, imm32 C Valid Valid Add imm32 to EAX.
	FCML_I32_M( "add ax,8042h", 2, FCML_MI( 0x66, 0x05, 0x42, 0x80 ), FCML_MI( 0x66, 0x81, 0xc0, 0x42, 0x80 ) );
	FCML_I32_D_FAILED( "add ax,8042h", 0xF0, 0x66, 0x05, 0x42, 0x80 );
	FCML_I32_A_FAILED( "add ax,8042h", 0xF0, 0x66, 0x05, 0x42, 0x80 );
	FCML_I32_M( "add eax,42806521h", 2, FCML_MI( 0x05, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x81, 0xc0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_D( "add eax,42806521h", 0x40, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_M( "add eax,42806521h", 2, FCML_MI( 0x05, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x81, 0xc0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_D( "add ax,6521h", 0x66, 0x40, 0x05, 0x21, 0x65 );
	FCML_I64_M( "add ax,6521h", 2, FCML_MI( 0x66, 0x05, 0x21, 0x65 ), FCML_MI( 0x66, 0x81, 0xc0, 0x21, 0x65 ) );
	// REX.W + 05 id ADD RAX, imm32 C Valid N.E. Add imm32 sign-extended to 64-bits to RAX.
	FCML_I64_D( "add rax,0000000042806521h", 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add rax,0000000042806521h", 0x66, 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add rax,0000000042806521h", 0x67, 0x66, 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add rax,0ffffffffffffffffh", 0x66, 0x67, 0x48, 0x05, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_M( "add rax,0000000042806521h", 2, FCML_MI( 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x48, 0x81, 0xc0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_M( "add rax,0ffffffffffffffffh", 3, FCML_MI( 0x48, 0x05, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x48, 0x81, 0xc0, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x48, 0x83, 0xc0, 0xff ) );
	// 80 /0 ib ADD r/m8, imm8 B Valid Valid Add imm8 to r/m8.
	// REX + 80 /0 ib ADD r/m8*, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	FCML_I32( "lock add byte ptr [04030201h],0ffh", 0xF0, 0x80, 0x05, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "add byte ptr [esi+04030201h],0ffh", 0x80, 0x86, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "add byte ptr [ecx+eax+00000002h],03h", 0x80, 0x44, 0x01, 0x02, 0x03 );
	FCML_I64( "add byte ptr [rcx+rax+0000000000000002h],03h", 0x80, 0x44, 0x01, 0x02, 0x03 );
	// 81 /0 iw ADD r/m16, imm16 B Valid Valid Add imm16 to r/m16.
	// 81 /0 id ADD r/m32, imm32 B Valid Valid Add imm32 to r/m32.
	FCML_I32( "add ebp,04030201h", 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32_A_FAILED( "lock add ebp,04030201h", 0xF0, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "add bp,0201h", 0x66, 0x81, 0xc5, 0x01, 0x02 );
	FCML_I64_D( "add bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xc5, 0x01, 0x02 );
	FCML_I64( "add bp,0201h", 0x66, 0x67, 0x81, 0xc5, 0x01, 0x02 );
	// REX.W + 81 /0 id ADD r/m64, imm32 B Valid N.E. Add imm32 sign-extended to 64-bits to r/m64.
	FCML_I64_D( "add rbp,0000000004030201h", 0x48, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64( "lock add qword ptr [rcx],0000000003020100h", 0xF0, 0x48, 0x81, 0x01, 0x00, 0x01, 0x02, 0x03 );
	FCML_I64_D( "add rbp,0ffffffffffffffffh", 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "add rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "add rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64( "add rbp,0000000004030201h", 0x48, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64_M( "add rbp,0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x48, 0x83, 0xc5, 0xff ) );
	// 83 /0 ib ADD r/m16, imm8 B Valid Valid Add sign-extended imm8 to r/m16.
	// 83 /0 ib ADD r/m32, imm8 B Valid Valid Add sign-extended imm8 to r/m32.
	FCML_I32_M( "lock add dword ptr [esi],00000001h", 2, FCML_MI( 0xF0, 0x83, 0x06, 0x01 ), FCML_MI( 0xF0, 0x81, 0x06, 0x01, 0x00, 0x00, 0x00 ) );
	FCML_I32_M( "add word ptr [esi],0001h", 2, FCML_MI( 0x66, 0x83, 0x06, 0x01 ), FCML_MI( 0x66, 0x81, 0x06, 0x01, 0x00 ) );
	FCML_I32_M( "add dword ptr [0201h],00000003h", 2, FCML_MI( 0x67, 0x83, 0x06, 0x01, 0x02, 0x03 ), FCML_MI( 0x67, 0x81, 0x06, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00 ) );
	// REX.W + 83 /0 ib ADD r/m64, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	FCML_I64_M( "lock add qword ptr [rdi+0000000004030201h],0000000000000005h", 2, FCML_MI( 0xF0, 0x48, 0x83, 0x87, 0x01, 0x02, 0x03, 0x4, 0x05 ), FCML_MI( 0xF0, 0x48, 0x81, 0x87, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00 ) );
	FCML_I64_M( "add qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x83, 0x87, 0x01, 0x02, 0x03, 0x4, 0xff ), FCML_MI( 0x48, 0x81, 0x87, 0x01, 0x02, 0x03, 0x04, 0xff, 0xff, 0xff, 0xff ) );
	// 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.
	// REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.
	FCML_I32( "lock add byte ptr [ebp+04030201h],ah", 0xF0, 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add byte ptr [rbp+0000000004030201h],spl", 0x40, 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add byte ptr [rbp+0000000000000001h],spl", 0x40, 0x00, 0x65, 0x01 );
	// 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.
	// 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.
	// REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.
	FCML_I32( "lock add dword ptr [ebp+04030201h],esp", 0xF0, 0x01, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "add word ptr [di+0201h],sp", 0x66, 0x67, 0x01, 0xa5, 0x01, 0x02 );
	FCML_I32( "add dword ptr [di+0201h],esp", 0x67, 0x01, 0xa5, 0x01, 0x02 );
	FCML_I64( "add qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x01, 0x64, 0x89, 0x01 );
	// 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.
	// REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.
	FCML_I32( "add ah,byte ptr [ebp+04030201h]", 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add spl,byte ptr [rbp+0000000004030201h]", 0x40, 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add spl,byte ptr [rbp+0000000000000001h]", 0x40, 0x02, 0x65, 0x01 );
	// 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.
	// 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.
	// REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.
	FCML_I32( "add esp,dword ptr [ebp+04030201h]", 0x03, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "add sp,word ptr [di+0201h]", 0x66, 0x67, 0x03, 0xa5, 0x01, 0x02 );
	FCML_I32( "add esp,dword ptr [di+0201h]", 0x67, 0x03, 0xa5, 0x01, 0x02 );
	FCML_I64( "add r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x03, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_ADDPD(void) {
	// 66 0F 58 /r ADDPD xmm1, xmm2/m128
	FCML_I32( "addpd xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );
	FCML_I64( "addpd xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );
	// VEX.NDS.128.66.0F 58 /r VADDPD xmm1,xmm2, xmm3/m128
	FCML_I64( "vaddpd ymm10,ymm14,ymmword ptr [r9+r8]", 0xC4, 0x01, 0x0D, 0x58, 0x14, 0x01 );
	// VAX.R VAX.B (3 byte VAX prefix.)
	FCML_I64( "vaddpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x58, 0x14, 0x01 );
	FCML_I64( "vaddpd xmm2,xmm14,xmmword ptr [r9+rax]", 0xC4, 0xC1, 0x09, 0x58, 0x14, 0x01 );
	// B bit is ignored in 32 bit mode.
	FCML_I32_D( "vaddpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x58, 0x14, 0x01 );
	FCML_I32_D( "vaddpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xE1, 0x69, 0x58, 0x14, 0x01 );
	FCML_I32_D( "vaddpd ymm2,ymm2,ymmword ptr [ecx+eax]", 0xC4, 0xE1, 0x6D, 0x58, 0x14, 0x01 );
	FCML_I32( "vaddpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC5, 0xE9, 0x58, 0x14, 0x01 );
	FCML_I32( "vaddpd ymm2,ymm2,ymmword ptr [ecx+eax]", 0xC5, 0xED, 0x58, 0x14, 0x01 );
	// VAX.L (0)
	FCML_I32( "vaddpd xmm2,xmm0,xmmword ptr [ecx+eax]", 0xC5, 0xF9, 0x58, 0x14, 0x01 );
	/// VEX.R (2 byte VEX prefix.)
	FCML_I64( "vaddpd ymm10,ymm4,ymmword ptr [rcx+rax]", 0xC5, 0x5D, 0x58, 0x14, 0x01 );
	// VAX.vvvv, VAX.L(1), VAX.pp
	FCML_I32( "vaddpd ymm2,ymm0,ymmword ptr [ecx+eax]", 0xC5, 0xFD, 0x58, 0x14, 0x01 );
}

void fcml_tf_instruction_ADDPS(void) {
	FCML_I32( "addps xmm2,xmmword ptr [ecx+eax]", 0x0F, 0x58, 0x14, 0x01 );
	FCML_I64( "addps xmm2,xmmword ptr [rcx+rax]", 0x0F, 0x58, 0x14, 0x01 );
}

void fcml_tf_instruction_ADDSD(void) {
	FCML_I32( "addsd xmm2,mmword ptr [ecx+eax]", 0xF2, 0x0F, 0x58, 0x14, 0x01 );
	FCML_I64( "addsd xmm2,mmword ptr [rcx+rax]", 0xF2, 0x0F, 0x58, 0x14, 0x01 );
	FCML_I32_D( "vaddsd xmm2,xmm5,mmword ptr [ecx+eax]", 0xC4, 0xE1, 0x53, 0x58, 0x14, 0x01 );
	FCML_I32( "vaddsd xmm2,xmm4,mmword ptr [ecx+eax]", 0xC5, 0xDB, 0x58, 0x14, 0x01 );
}

void fcml_tf_instruction_ADDSS(void) {
	FCML_I32( "addss xmm2,dword ptr [ecx+eax]", 0xF3, 0x0F, 0x58, 0x14, 0x01 );
	FCML_I64( "addss xmm2,dword ptr [rcx+rax]", 0xF3, 0x0F, 0x58, 0x14, 0x01 );
	// VEX.NDS.128.F3.0F 58 /r VADDSS xmm1,xmm2, xmm3/m32
	FCML_I32_D( "vaddss xmm2,xmm5,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x52, 0x58, 0x14, 0x01 );
	FCML_I32( "vaddss xmm2,xmm4,dword ptr [ecx+eax]", 0xC5, 0xDA, 0x58, 0x14, 0x01 );
}

void fcml_tf_instruction_ADDSUBPD(void) {
	FCML_I32( "addsubpd xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0xD0, 0x14, 0x01 );
	FCML_I64( "addsubpd xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0xD0, 0x14, 0x01 );
	// VEX.NDS.128.66.0F D0 /r VADDSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F D0 /r VADDSUBPD ymm1, ymm2,ymm3/m256
	FCML_I64( "vaddsubpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0xD0, 0x14, 0x01 );
	FCML_I32_D( "vaddsubpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0xD0, 0x14, 0x01 );
	FCML_I32_D( "vaddsubpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0xD0, 0x14, 0x01 );
	FCML_I32( "vaddsubpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC5, 0xC1, 0xD0, 0x14, 0x01 );
	FCML_I32( "vaddsubpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC5, 0xE9, 0xD0, 0x14, 0x01 );
}

void fcml_tf_instruction_ADDSUBPS(void) {
	FCML_I32( "addsubps xmm2,xmmword ptr [ecx+eax]", 0xf2, 0x0F, 0xD0, 0x14, 0x01 );
	FCML_I64( "addsubps xmm2,xmmword ptr [rcx+rax]", 0xf2, 0x0F, 0xD0, 0x14, 0x01 );
	// VEX.NDS.128.F2.0F D0 /r VADDSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F D0 /r VADDSUBPS ymm1, ymm2,ymm3/m256
	FCML_I64( "vaddsubps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0xD0, 0x14, 0x01 );
	FCML_I64( "vaddsubps xmm2,xmm14,xmmword ptr [r9+rax]", 0xC4, 0xC1, 0x0B, 0xD0, 0x14, 0x01 );
	FCML_I32_D( "vaddsubps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xC1, 0x6B, 0xD0, 0x14, 0x01 );
	FCML_I32( "vaddsubps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC5, 0xEB, 0xD0, 0x14, 0x01 );
	FCML_I32( "vaddsubps xmm2,xmm6,xmmword ptr [ecx+eax]", 0xC5, 0xCB, 0xD0, 0x14, 0x01 );
}

void fcml_tf_instruction_AESDEC(void) {
	FCML_I32( "aesdec xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDE, 0x14, 0x01 );
	FCML_I64( "aesdec xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDE, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DE /r VAESDEC xmm1,xmm2,xmm3/m128
	FCML_I32( "vaesdec xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDE, 0x00 );
	FCML_I32( "vaesdec xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDE, 0xC0 );
	FCML_I64( "vaesdec xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDE, 0x00 );
}

void fcml_tf_instruction_AESDECLAST(void) {
	FCML_I32( "aesdeclast xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDF, 0x14, 0x01 );
	FCML_I64( "aesdeclast xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDF, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DF /r VAESDECLAST xmm1,xmm2,xmm3/m128
	FCML_I32( "vaesdeclast xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDF, 0x00 );
	FCML_I32( "vaesdeclast xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDF, 0xC0 );
	FCML_I64( "vaesdeclast xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDF, 0x00 );
}

void fcml_tf_instruction_AESENC(void) {
	FCML_I32( "aesenc xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDC, 0x14, 0x01 );
	FCML_I64( "aesenc xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDC, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DC /r VAESENC xmm1, xmm2, xmm3/m128
	FCML_I32( "vaesenc xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDC, 0x00 );
	FCML_I32( "vaesenc xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDC, 0xC0 );
	FCML_I64( "vaesenc xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDC, 0x00 );
}

void fcml_tf_instruction_AESENCLAST(void) {
	FCML_I32( "aesenclast xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDD, 0x14, 0x01 );
	FCML_I64( "aesenclast xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDD, 0x14, 0x01 );
	// VEX.NDS.128.66.0F38.WIG DD /r VAESENCLAST xmm1,xmm2,xmm3/m128
	FCML_I32( "vaesenclast xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDD, 0x00 );
	FCML_I32( "vaesenclast xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDD, 0xC0 );
	FCML_I64( "vaesenclast xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDD, 0x00 );
}

void fcml_tf_instruction_AESIMC(void) {
	FCML_I32( "aesimc xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x38, 0xDB, 0x14, 0x01 );
	FCML_I64( "aesimc xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x38, 0xDB, 0x14, 0x01 );
	// VEX.128.66.0F38.WIG DB /r VAESIMC xmm1, xmm2/m128
	FCML_I32( "vaesimc xmm0,xmm3,xmmword ptr [eax]", 0xC4, 0xE2, 0x61, 0xDB, 0x00 );
	FCML_I32( "vaesimc xmm0,xmm3,xmm0", 0xC4, 0xE2, 0x61, 0xDB, 0xC0 );
	FCML_I64( "vaesimc xmm0,xmm3,xmmword ptr [rax]", 0xC4, 0xE2, 0x61, 0xDB, 0x00 );
}

void fcml_tf_instruction_AESKEYGENASSIST(void) {
	FCML_I32( "aeskeygenassist xmm2,xmmword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0xDF, 0x14, 0x01, 0xFF );
	FCML_I64( "aeskeygenassist xmm2,xmmword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0xDF, 0x14, 0x01, 0xFF );
	// VEX.128.66.0F3A.WIG DF /r ib VAESKEYGENASSIST xmm1,xmm2/m128,imm8
	FCML_I32( "vaeskeygenassist xmm0,xmmword ptr [eax],0ffh", 0xC4, 0xE3, 0x79, 0xDF, 0x00, 0xFF );
	FCML_I32( "vaeskeygenassist xmm0,xmm0,0ffh", 0xC4, 0xE3, 0x79, 0xDF, 0xC0, 0xFF );
}

void fcml_tf_instruction_AND(void) {
	// 24 ib AND AL, imm8 C Valid Valid AL AND imm8.
	FCML_I32_M( "and al,42h", 2, FCML_MI( 0x24, 0x42 ), FCML_MI( 0x80, 0xE0, 0x42 ) );
	FCML_I32_M( "and al,0ffh", 2, FCML_MI( 0x24, 0xFF ), FCML_MI( 0x80, 0xE0, 0xFF ) );
	FCML_I32_M( "and al,00h", 2, FCML_MI( 0x24, 0x00 ), FCML_MI( 0x80, 0xE0, 0x00 ) );
	FCML_I32_M( "and al,0ffh", 2, FCML_MI( 0x24, 0xFF ), FCML_MI( 0x80, 0xE0, 0xFF ) );
	// 25 iw AND AX, imm16 C Valid Valid AX AND imm16.
	// 25 id AND EAX, imm32 C Valid Valid EAX AND imm32.
	FCML_I32_M( "and ax,8042h", 2, FCML_MI( 0x66, 0x25, 0x42, 0x80 ), FCML_MI( 0x66, 0x81, 0xE0, 0x42, 0x80 ) );
	FCML_I32_M( "and eax,42806521h", 2, FCML_MI( 0x25, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x81, 0xe0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_D( "and eax,42806521h", 0x40, 0x25, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "and ax,6521h", 0x66, 0x40, 0x25, 0x21, 0x65 );
	// REX.W + 25 id AND RAX, imm32 C Valid N.E. RAX AND imm32 signextended to 64-bits.
	FCML_I64_M( "and rax,0000000042806521h", 2, FCML_MI( 0x48, 0x25, 0x21, 0x65, 0x80, 0x42 ), FCML_MI(0x48, 0x81, 0xe0, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_I64_D( "and rax,0000000042806521h", 0x66, 0x48, 0x25, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "and rax,0000000042806521h", 0x67, 0x66, 0x48, 0x25, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "and rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x25, 0xff, 0xff, 0xff, 0xff );
	// 80 /4 ib AND r/m8, imm8 B Valid Valid r/m8 AND imm8.
	// REX + 80 /4 ib AND r/m8*, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	FCML_I32( "and byte ptr [04030201h],0ffh", 0x80, 0x25, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "and byte ptr [esi+04030201h],0ffh", 0x80, 0xA6, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "and byte ptr [ecx+eax+00000002h],03h", 0x80, 0x64, 0x01, 0x02, 0x03 );
	// 81 /4 iw AND r/m16, imm16 B Valid Valid r/m16 AND imm16.
	// 81 /4 id AND r/m32, imm32 B Valid Valid r/m32 AND imm32.
	FCML_I32( "and ebp,04030201h", 0x81, 0xe5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "and bp,0201h", 0x66, 0x81, 0xe5, 0x01, 0x02 );
	FCML_I64_D( "and bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xe5, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /4 id AND r/m64, imm32 B Valid N.E. r/m64 AND imm32 sign extended to 64-bits.
	FCML_I64( "and rbp,0000000004030201h", 0x48, 0x81, 0xe5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64_M( "and rbp,0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x81, 0xe5, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x48, 0x83, 0xe5, 0xff ) );
	FCML_I64_M( "and rbp,0ffffffffffffffffh", 2, FCML_MI( 0x67, 0x48, 0x81, 0xe5, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x67, 0x48, 0x83, 0xe5, 0xff ) );
	FCML_I64_D( "and rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xe5, 0xff, 0xff, 0xff, 0xff );
	// 83 /4 ib AND r/m16, imm8 B Valid Valid r/m16 AND imm8 (signextended).
	// 83 /4 ib AND r/m32, imm8 B Valid Valid r/m32 AND imm8 (signextended).
	FCML_I32_M( "and dword ptr [esi],00000001h", 2, FCML_MI( 0x83, 0x26, 0x01 ), FCML_MI( 0x81, 0x26, 0x01, 0x00, 0x00, 0x00 ) );
	FCML_I32_M( "and word ptr [esi],0001h", 2, FCML_MI( 0x66, 0x83, 0x26, 0x01 ), FCML_MI( 0x66, 0x81, 0x26, 0x01, 0x00 ) );
	FCML_I32_M( "and dword ptr [0201h],00000003h", 2, FCML_MI( 0x67, 0x83, 0x26, 0x01, 0x02, 0x03 ), FCML_MI( 0x67, 0x81, 0x26, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00 ) );
	// REX.W + 83 /4 ib AND r/m64, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	FCML_I64_M( "and qword ptr [rdi+0000000004030201h],0000000000000005h", 2, FCML_MI( 0x48, 0x83, 0xA7, 0x01, 0x02, 0x03, 0x4, 0x05 ), FCML_MI( 0x48, 0x81, 0xa7, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00 ) );
	FCML_I64_M( "and qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x83, 0xA7, 0x01, 0x02, 0x03, 0x4, 0xff ), FCML_MI( 0x48, 0x81, 0xa7, 0x01, 0x02, 0x03, 0x04, 0xff, 0xff, 0xff, 0xff ) );
	// 20 /r AND r/m8, r8 A Valid Valid r/m8 AND r8.
	// REX + 20 /r AND r/m8*, r8* A Valid N.E. r/m64 AND r8 (signextended).
	FCML_I32( "and byte ptr [ebp+04030201h],ah", 0x20, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64_D( "and byte ptr [rbp+0000000004030201h],spl", 0x48, 0x20, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64_D( "and byte ptr [rbp+0000000000000001h],spl", 0x48, 0x20, 0x64, 0xa5, 0x01 );
	FCML_I64( "and byte ptr [rbp+0000000000000001h],spl", 0x40, 0x20, 0x65, 0x01 );
	// 21 /r AND r/m16, r16 A Valid Valid r/m16 AND r16.
	// 21 /r AND r/m32, r32 A Valid Valid r/m32 AND r32.
	// REX.W + 21 /r AND r/m64, r64 A Valid N.E. r/m64 AND r32.
	FCML_I32( "and dword ptr [ebp+04030201h],esp", 0x21, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "and word ptr [di+0201h],sp", 0x66, 0x67, 0x21, 0xa5, 0x01, 0x02 );
	FCML_I32( "and dword ptr [di+0201h],esp", 0x67, 0x21, 0xa5, 0x01, 0x02 );
	FCML_I32_M( "and edi,edx", 2, FCML_MI( 0x21, 0xD7 ), FCML_MI(0x23, 0xfa) );
	FCML_I32_M( "and di,dx", 2, FCML_MI( 0x66, 0x21, 0xD7 ), FCML_MI( 0x66, 0x23, 0xfa ) );
	FCML_I32_M( "and edi,edx", 2, FCML_MI( 0x67, 0x21, 0xD7 ), FCML_MI( 0x67, 0x23, 0xfa ) );
	FCML_I32( "and dword ptr [030201a5h],eax",  0x21, 0x05, 0xa5, 0x01, 0x02, 0x03 );
	FCML_I32( "and dword ptr [01a5h],eax",  0x67, 0x21, 0x06, 0xa5, 0x01 );
	FCML_I32( "and dword ptr [ebp+00000001h],ecx",  0x21, 0x4d, 0x01 );
	FCML_I32_D( "and dword ptr [50030201h],ecx",  0x21, 0x0c, 0x25, 0x01, 0x02, 0x03, 0x50 );
	FCML_I32( "and dword ptr [50030201h],ecx",  0x21, 0x0d, 0x01, 0x02, 0x03, 0x50 );
	FCML_I64_D( "and qword ptr [rbp+0000000000000001h],rcx",  0x48, 0x21, 0x4c, 0x25, 0x01 );
	FCML_I64( "and qword ptr [rbp+0000000000000001h],rcx",  0x48, 0x21, 0x4d, 0x01 );
	FCML_I64_D( "and qword ptr [00008000034211ach],rax",  0x48, 0x21, 0x05, 0xa5, 0x01, 0x02, 0x03 );
	FCML_I64_RIP( "and qword ptr [00008000034211ach],rax",  0x48, 0x21, 0x05, 0xa5, 0x01, 0x02, 0x03 );
	FCML_I64( "and qword ptr [rcx+rsi*4],rax",  0x48, 0x21, 0x04, 0xB1 );
	FCML_I64( "and qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x21, 0x64, 0x89, 0x01 );
	FCML_I32_D( "and dword ptr [ebp+00000001h],ebx",  0x21, 0x5C, 0xA5, 0x01 );
	FCML_I32( "and dword ptr [ebp+00000001h],ebx",  0x21, 0x5D, 0x01 );
	FCML_I32_D( "and dword ptr [ebp+04030201h],ebx",  0x21, 0x9C, 0xA5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "and dword ptr [ebp+04030201h],ebx",  0x21, 0x9D, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32_D( "and dword ptr [04030201h],ebx",  0x21, 0x1C, 0xA5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "and dword ptr [04030201h],ebx",  0x21, 0x1D, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32_D( "and dword ptr [04030201h],edx",  0x21, 0x14, 0x25, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "and dword ptr [04030201h],edx",  0x21, 0x15, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32_D( "and dword ptr [eax],edx",  0x21, 0x14, 0x20 ); // DUAL
	FCML_I32( "and dword ptr [eax],edx",  0x21, 0x10 ); // DUAL
	FCML_I32_D( "and dword ptr [ecx],edx",  0x21, 0x14, 0x21  ); // DUAL
	FCML_I32( "and dword ptr [ecx],edx",  0x21, 0x11  ); // DUAL
	FCML_I32_D( "and dword ptr [edx],edx",  0x21, 0x14, 0x22 ); // DUAL
	FCML_I32( "and dword ptr [edx],edx",  0x21, 0x12 ); // DUAL
	FCML_I32_D( "and dword ptr [ebx],edx",  0x21, 0x14, 0x23 ); // DUAL
	FCML_I32( "and dword ptr [ebx],edx",  0x21, 0x13 ); // DUAL
	FCML_I32( "and dword ptr [esp],edx",  0x21, 0x14, 0x24 ); // SIB ONLY
	FCML_I32_D( "and dword ptr [04030201h],edx",  0x21, 0x14, 0x25, 0x01, 0x02, 0x03, 0x04 ); // DUAL
	FCML_I32( "and dword ptr [04030201h],edx",  0x21, 0x15, 0x01, 0x02, 0x03, 0x04 ); // DUAL
	FCML_I32_D( "and dword ptr [esi],edx",  0x21, 0x14, 0x26 ); // DUAL
	FCML_I32( "and dword ptr [esi],edx",  0x21, 0x16 ); // DUAL
}

void fcml_tf_instruction_ANDPD(void) {
	FCML_I32( "andpd xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x54, 0x14, 0x01 );
	FCML_I64( "andpd xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x54, 0x14, 0x01 );
	// VEX.NDS.128.66.0F 54 /r VANDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 54 /r VANDPD ymm1,ymm2,ymm3/m256
	FCML_I64( "vandpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x54, 0x14, 0x01 );
	FCML_I32( "vandpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xC5, 0xC1, 0x54, 0x14, 0x01 );
	FCML_I32( "vandpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xC5, 0xE9, 0x54, 0x14, 0x01 );
	FCML_I32( "vandpd xmm2,xmm6,xmmword ptr [ecx+eax]", 0xC5, 0xC9, 0x54, 0x14, 0x01 );
}

void fcml_tf_instruction_ANDPS(void) {
	FCML_I32( "andps xmm2,xmmword ptr [ecx+eax]", 0x0F, 0x54, 0x14, 0x01 );
	FCML_I64( "andps xmm2,xmmword ptr [rcx+rax]", 0x0F, 0x54, 0x14, 0x01 );
	// VEX.NDS.128.0F 54 /r VANDPS xmm1,xmm2, xmm3/m128
	// VEX.NDS.256.0F 54 /r VANDPS ymm1, ymm2, ymm3/m256
	FCML_I64( "vandps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x54, 0x14, 0x01 );
	FCML_I32( "vandps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc0, 0x54, 0x14, 0x01 );
	FCML_I32( "vandps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xe8, 0x54, 0x14, 0x01 );
	FCML_I32( "vandps xmm2,xmm6,xmmword ptr [ecx+eax]", 0xC5, 0xC8, 0x54, 0x14, 0x01 );
}

void fcml_tf_instruction_ANDNPD(void) {
	FCML_I32( "andnpd xmm2,xmmword ptr [ecx+eax]", 0x66, 0x0F, 0x55, 0x14, 0x01 );
	FCML_I64( "andnpd xmm2,xmmword ptr [rcx+rax]", 0x66, 0x0F, 0x55, 0x14, 0x01 );
	// VEX.NDS.128.66.0F 55 /r VANDNPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 55 /r VANDNPD ymm1,ymm2,ymm3/m256
	FCML_I64( "vandnpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x55, 0x14, 0x01 );
	FCML_I32( "vandnpd xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc1, 0x55, 0x14, 0x01 );
	FCML_I32( "vandnpd xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xe9, 0x55, 0x14, 0x01 );
	FCML_I32( "vandnpd xmm2,xmm6,xmmword ptr [ecx+eax]", 0xC5, 0xC9, 0x55, 0x14, 0x01 );
}

void fcml_tf_instruction_ANDNPS(void) {
	FCML_I32( "andnps xmm2,xmmword ptr [ecx+eax]", 0x0F, 0x55, 0x14, 0x01 );
	FCML_I64( "andnps xmm2,xmmword ptr [rcx+rax]", 0x0F, 0x55, 0x14, 0x01 );
	// VEX.NDS.128.0F 55 /r VANDNPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 55 /r VANDNPS ymm1,ymm2,ymm3/m256
	FCML_I64( "vandnps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0C, 0x55, 0x14, 0x01 );
	FCML_I32( "vandnps xmm2,xmm7,xmmword ptr [ecx+eax]", 0xc5, 0xc0, 0x55, 0x14, 0x01 );
	FCML_I32( "vandnps xmm2,xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xe8, 0x55, 0x14, 0x01 );
	FCML_I32( "vandnps xmm2,xmm6,xmmword ptr [ecx+eax]", 0xC5, 0xC8, 0x55, 0x14, 0x01 );
}

void fcml_tf_instruction_ARPL(void) {
	FCML_I32( "arpl word ptr [ecx+eax],dx", 0x63, 0x14, 0x01 );
	FCML_I32_D( "arpl word ptr [ecx+eax],dx", 0x66, 0x63, 0x14, 0x01 );
	FCML_I32( "arpl word ptr [si],dx", 0x67, 0x63, 0x14 );
	FCML_I64_FAILED( "arpl edi", 0x63, 0xDF );
}

void fcml_tf_instruction_ANDN(void) {
	// VEX.NDS.LZ.0F38.W0 F2 /r ANDN r32a, r32b, r/m32
	FCML_I32( "andn eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF2, 0x00 );
	FCML_I32( "andn eax,edi,eax", 0xC4, 0xE2, 0x40, 0xF2, 0xC0 );
	// VEX.NDS.LZ.0F38.W1 F2 /r ANDN r64a, r64b, r/m64
	FCML_I32( "andn rax,rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF2, 0x00 );
	FCML_I32( "andn rax,rdi,rax", 0xC4, 0xE2, 0xC0, 0xF2, 0xC0 );
}

void fcml_tf_instruction_ADCX(void) {
	// 66 0F 38 F6 /r ADCX r32, r/m32
	// REX.W + 66 0F 38 F6 /r ADCX r64,r/m64
	FCML_I32( "adcx eax,dword ptr [eax]", 0x66, 0x0F, 0x38, 0xF6, 0x00 );
	FCML_I64( "adcx eax,dword ptr [rax]", 0x66, 0x0F, 0x38, 0xF6, 0x00 );
	FCML_I64( "adcx rax,qword ptr [rax]", 0x66, 0x48, 0x0F, 0x38, 0xF6, 0x00 );
}

void fcml_tf_instruction_ADOX(void) {
	// F3 0F 38 F6 /r ADOX r32, r/m32
	// REX.w + F3 0F 38 F6 /r ADOX r64, r/m64
	FCML_I32( "adox eax,dword ptr [eax]", 0xF3, 0x0F, 0x38, 0xF6, 0x00 );
	FCML_I64( "adox eax,dword ptr [rax]", 0xF3, 0x0F, 0x38, 0xF6, 0x00 );
	FCML_I64( "adox rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0x38, 0xF6, 0x00 );
}

CU_TestInfo fctl_ti_instructions_a[] = {
    { "fcml_tf_instruction_AAA", fcml_tf_instruction_AAA },
    { "fcml_tf_instruction_AAD", fcml_tf_instruction_AAD },
    { "fcml_tf_instruction_AAM", fcml_tf_instruction_AAM },
    { "fcml_tf_instruction_AAS", fcml_tf_instruction_AAS },
    { "fcml_tf_instruction_ADC", fcml_tf_instruction_ADC },
    { "fcml_tf_instruction_ADD", fcml_tf_instruction_ADD },
    { "fcml_tf_instruction_ADDPD", fcml_tf_instruction_ADDPD },
    { "fcml_tf_instruction_ADDPS", fcml_tf_instruction_ADDPS },
    { "fcml_tf_instruction_ADDSD", fcml_tf_instruction_ADDSD },
    { "fcml_tf_instruction_ADDSS", fcml_tf_instruction_ADDSS },
    { "fcml_tf_instruction_ADDSUBPD", fcml_tf_instruction_ADDSUBPD },
    { "fcml_tf_instruction_ADDSUBPS", fcml_tf_instruction_ADDSUBPS },
    { "fcml_tf_instruction_AESDEC", fcml_tf_instruction_AESDEC },
    { "fcml_tf_instruction_AESDECLAST", fcml_tf_instruction_AESDECLAST },
    { "fcml_tf_instruction_AESENC", fcml_tf_instruction_AESENC },
    { "fcml_tf_instruction_AESENCLAST", fcml_tf_instruction_AESENCLAST },
    { "fcml_tf_instruction_AESIMC", fcml_tf_instruction_AESIMC },
    { "fcml_tf_instruction_AESKEYGENASSIST", fcml_tf_instruction_AESKEYGENASSIST },
    { "fcml_tf_instruction_AND", fcml_tf_instruction_AND },
    { "fcml_tf_instruction_ANDPD", fcml_tf_instruction_ANDPD },
    { "fcml_tf_instruction_ANDPS", fcml_tf_instruction_ANDPS },
    { "fcml_tf_instruction_ANDNPD", fcml_tf_instruction_ANDNPD },
    { "fcml_tf_instruction_ANDNPS", fcml_tf_instruction_ANDNPS },
    { "fcml_tf_instruction_ARPL", fcml_tf_instruction_ARPL },
    { "fcml_tf_instruction_ANDN", fcml_tf_instruction_ANDN },
    { "fcml_tf_instruction_ADCX", fcml_tf_instruction_ADCX },
    { "fcml_tf_instruction_ADOX", fcml_tf_instruction_ADOX },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_a[] = {
    { "suite-fctl_ti_instructions_a", fcml_tf_instructions_a_suite_init, fcml_tf_instructions_a_suite_cleanup, fctl_ti_instructions_a },
    CU_SUITE_INFO_NULL,
};
