#ifndef IRA_H_INCLUDED
#define IRA_H_INCLUDED

#include <inttypes.h>

#define _IRA_OPERANDS_COUNT						4
#define _IRA_PREFIXES_COUNT						12

#define _IRA_TRUE		1
#define _IRA_FALSE		0

/* Registers */

#define _IRA_REG_AL		0
#define _IRA_REG_AX		0
#define _IRA_REG_EAX	0
#define _IRA_REG_RAX	0
#define _IRA_REG_MM0	0
#define _IRA_REG_XMM0	0

#define _IRA_REG_CL		1
#define _IRA_REG_CX		1
#define _IRA_REG_ECX	1
#define _IRA_REG_RCX	1
#define _IRA_REG_MM1	1
#define _IRA_REG_XMM1	1

#define _IRA_REG_DL		2
#define _IRA_REG_DX		2
#define _IRA_REG_EDX	2
#define _IRA_REG_RDX	2
#define _IRA_REG_MM2	2
#define _IRA_REG_XMM2	2

#define _IRA_REG_BL		3
#define _IRA_REG_BX		3
#define _IRA_REG_EBX	3
#define _IRA_REG_RBX	3
#define _IRA_REG_MM3	3
#define _IRA_REG_XMM3	3

#define _IRA_REG_AH		4
#define _IRA_REG_SP		4
#define _IRA_REG_ESP	4
#define _IRA_REG_RSP	4
#define _IRA_REG_MM4	4
#define _IRA_REG_XMM4	4

#define _IRA_REG_CH		5
#define _IRA_REG_BP		5
#define _IRA_REG_EBP	5
#define _IRA_REG_RBP	5
#define _IRA_REG_MM5	5
#define _IRA_REG_XMM5	5

#define _IRA_REG_DH		6
#define _IRA_REG_SI		6
#define _IRA_REG_ESI	6
#define _IRA_REG_RSI	6
#define _IRA_REG_MM6	6
#define _IRA_REG_XMM6	6

#define _IRA_REG_BH		7
#define _IRA_REG_DI		7
#define _IRA_REG_EDI	7
#define _IRA_REG_RDI	7
#define _IRA_REG_MM7	7
#define _IRA_REG_XMM7	7

#define _IRA_REG_R8L	8
#define _IRA_REG_R8W	8
#define _IRA_REG_R8D	8
#define _IRA_REG_R8		8
#define _IRA_REG_XMM8	8

#define _IRA_REG_R9L	9
#define _IRA_REG_R9W	9
#define _IRA_REG_R9D	9
#define _IRA_REG_R9		9
#define _IRA_REG_XMM9	9

#define _IRA_REG_R10L	10
#define _IRA_REG_R10W	10
#define _IRA_REG_R10D	10
#define _IRA_REG_R10	10
#define _IRA_REG_XMM10	10

#define _IRA_REG_R11L	11
#define _IRA_REG_R11W	11
#define _IRA_REG_R11D	11
#define _IRA_REG_R11	11
#define _IRA_REG_XMM11	11

#define _IRA_REG_R12L	12
#define _IRA_REG_R12W	12
#define _IRA_REG_R12D	12
#define _IRA_REG_R12	12
#define _IRA_REG_XMM12	12

#define _IRA_REG_R13L	13
#define _IRA_REG_R13W	13
#define _IRA_REG_R13D	13
#define _IRA_REG_R13	13
#define _IRA_REG_XMM13	13

#define _IRA_REG_R14L	14
#define _IRA_REG_R14W	14
#define _IRA_REG_R14D	14
#define _IRA_REG_R14	14
#define _IRA_REG_XMM14	14

#define _IRA_REG_R15L	15
#define _IRA_REG_R15W	15
#define _IRA_REG_R15D	15
#define _IRA_REG_R15	15
#define _IRA_REG_XMM15	15

/* Segment registers */

#define _IRA_SEG_REG_NONE	0
#define _IRA_SEG_REG_CS		1
#define _IRA_SEG_REG_DS 	2
#define _IRA_SEG_REG_SS 	3
#define _IRA_SEG_REG_ES 	4
#define _IRA_SEG_REG_FS 	5
#define _IRA_SEG_REG_GS 	6

/* Size directives */

#define _IRA_SD_BYTE_PTR		8
#define _IRA_SD_WORD_PTR		16
#define _IRA_SD_DWORD_PTR		32
#define _IRA_SD_FWORD_PTR		48
#define _IRA_SD_QWORD_PTR		64
#define _IRA_SD_MMWORD_PTR		64
#define _IRA_SD_TBYTE_PTR		80
#define _IRA_SD_OWORD_PTR		128
#define _IRA_SD_XMMWORD_PTR		128

/* Data types. */
#define _IRA_DT_UNKNOWN			0x0000

/* IRA conditions. */

enum ira_condition_type {
	_IRA_CONDITION_O = 0,		// 0 Overflow
	_IRA_CONDITION_B,		// 1 Below
	_IRA_CONDITION_E,		// 2 Equal
	_IRA_CONDITION_BE,		// 3 Below or equal
	_IRA_CONDITION_S,		// 4 Sign
	_IRA_CONDITION_P,		// 5 Parity
	_IRA_CONDITION_L,		// 6 Less than
	_IRA_CONDITION_LE		// 7 Less than or equal to
};

/* Common data types. */

struct ira_nullable_byte {
	// 0 if null, otherwise 1.
	uint8_t is_not_null;
	// Value.
	uint8_t value;
} typedef n_byte;

struct ira_nullable_word {
	// 0 if null, otherwise 1.
	uint16_t is_not_null;
	// Value.
	uint16_t value;
} typedef n_word;


enum ira_operation_mode {
	IRA_MOD_16BIT,
	IRA_MOD_32BIT,
	IRA_MOD_64BIT
};

enum ira_result_code {
	RC_OK = 0,
	RC_ERROR_ILLEGAL_OPERATION_MODE,
	RC_ERROR_ILLEGAL_ADDRESS_SIZE_ATTRIBUTE,
	RC_ERROR_ILLEGAL_OPERAND_SIZE_ATTRIBUTE,
	// When disassembler is not able to disassemble instruction due to incomplete data in stream.
	RC_ERROR_INSTRUCTION_INCOMPLETE,
	RC_ERROR_OUT_OF_MEMORY,
	RC_ERROR_UNEXPECTED_INTERNAL_ERROR,
	RC_ERROR_ILLEGAL_ADDRESSING_MODE,
	RC_ERROR_INSTRUCTION_NOT_ENCODABLE,
	RC_ERROR_SYNTAX_NOT_SUPPORTED,
	RC_ERROR_ILLEGAL_INSTRUCTION
};

enum ira_operand_type {
	IRA_NONE = 0,
	IRA_ADDRESS,
	IRA_IMMEDIATE_DATA,
	IRA_REGISTER
};

/*
 * Important aspect of RIP-relative addressing is, that it is not possible to use any other register
 * in the address, like [RIP+EAX] or similar. Another (not so obvious) aspect of RIP-relative addressing
 * is fact, that it is (just like any other addressing) controlled by address-size override prefix 67.
 * With this prefix, it is possible to address relative to EIP:
 * 67 8B 05 10 00 00 00   MOV EAX, [EIP+10h]
 */

enum ira_register_type {
	IRA_NO_REG = 0,
	IRA_REG_GPR_8,
	IRA_REG_GPR_16,
	IRA_REG_GPR_32,
	IRA_REG_GPR_64,
	IRA_REG_MMX,
	IRA_REG_XMM,
	IRA_REG_GPR
};

/* Common structure to describe register. */
struct ira_register {
	// Type of the register encoded in next field.
	enum ira_register_type reg_type;
	// Register.
	int reg;
};

// Allowed values of size attributes (ASA/OSA).
#define _IRA_GSA_16		16
#define _IRA_GSA_32		32
#define _IRA_GSA_64		64

/* Constants describing allowed values of operand size attribute. */
#define _IRA_OSA_16		_IRA_GSA_16
#define _IRA_OSA_32		_IRA_GSA_32
#define _IRA_OSA_64		_IRA_GSA_64

/* Constants describing allowed values of address size attribute. */
#define _IRA_ASA_16		_IRA_GSA_16
#define _IRA_ASA_32		_IRA_GSA_32
#define _IRA_ASA_64		_IRA_GSA_64

union ira_instruction_pointer {
	uint32_t eip;
	uint64_t rip;
};

struct ira_disassemble_info {
	/* Architecture. */
	enum ira_operation_mode mode;
	/* Operand size attribute. */
	uint16_t operand_size_attribute;
	/* Address size attribute. */
	uint16_t address_size_attribute;
	/* Address of the code to disassemble. */
	void *address;
	/* Size of the data to disassemble. */
	uint32_t size;
	/* Instruction pointer. In case of 32 bit addressing, only lower 32 bits are used and so on. */
	union ira_instruction_pointer instruction_pointer;
};

enum ira_immediate_data_type {
	IRA_NO_IMMEDIATE_DATA = 0,
	IRA_IMMEDIATE_8 = 8,
	IRA_IMMEDIATE_16 = 16,
	IRA_IMMEDIATE_32 = 32,
	IRA_IMMEDIATE_64 = 64
};

union ira_immediate_data_value {
	uint8_t immediate_8;
	uint16_t immediate_16;
	uint32_t immediate_32;
	uint64_t immediate_64;
};

struct ira_immediate_data {
	// Immediate data type.
	enum ira_immediate_data_type immediate_data_type;
	// Immediate data.
	union ira_immediate_data_value immediate_data;
	// Value set to the size value is extended to. 0 mean no extension.
	uint8_t extension_size;
};

enum ira_displacement_type {
	IRA_NO_DISPLACEMENT = 0,
	IRA_DISPLACEMENT_8 = 8,
	IRA_DISPLACEMENT_16 = 16,
	IRA_DISPLACEMENT_32 = 32,
};

/* Size of the displacement after sign extending. */
enum ira_displacement_extension_size {
	IRA_DISPLACEMENT_EXT_SIZE_16 = 16,
	IRA_DISPLACEMENT_EXT_SIZE_32 = 32,
	IRA_DISPLACEMENT_EXT_SIZE_64 = 64
};

union ira_displacement_value {
	uint8_t displacement_8;
	uint16_t displacement_16;
	uint32_t displacement_32;
};

struct ira_displacement {
	// Size of the displacement value.
	enum ira_displacement_type displacement_type;
	// Size of the displacement after sign extending.
	enum ira_displacement_extension_size extension_size;
	// Displacement value.
	union ira_displacement_value displacement;
};

enum ira_addressing_type {
	IRA_MOD_RM,
	IRA_IMMEDIATE_ADDRESS,
	IRA_RELATIVE_ADDRESS,
	IRA_FAR_POINTER,
	IRA_IMPLICIT_REGISTER_ADDRESSING
};

enum ira_access_mode {
	IRA_ACCESS_MODE_UNDEFINED,
	IRA_READ,
	IRA_WRITE,
	IRA_READ_RITE
};

struct ira_mod_rm_addressing {
	// ModRM byte.
	n_byte raw_mod_rm;
	// SIB byte.
	n_byte raw_sib;
	// REX prefix.
	n_byte raw_rex;
	// Base register.
	struct ira_register base_reg;
	// Index register.
	struct ira_register index_reg;
	// Scale factor value for 32 and 64 bit addressing modes.
	n_byte scale;
	// Displacement value.
	struct ira_displacement displacement;
};

enum ira_address_size {
	IRA_ADDRESS_16 = 16,
	IRA_ADDRESS_32 = 32,
	IRA_ADDRESS_64 = 64
};

union ira_address_value {
	uint16_t address_16;
	uint32_t address_32;
	uint64_t address_64;
};

struct ira_segment_selector {
	// Type of the segment register using with addressing.
	uint8_t segment_register;
	// Value destined for the segment register, for example see: "ptr16:32" addressing mode.
	uint16_t segment_register_value;
};

/* Used to describe size and format/meaning of
 * data accessed by addressing mode or register.
 */
struct ira_data_type {
	// Used to calculate size directive. It's size of the data
	// accessed using given addressing mode or register. Size in bytes.
	uint16_t data_size;
	// Type of the accessed data. Apart of the size in bytes every
	// data can have specific format and meaning in given context.
	// For example some instructions can treat XMM registers as
	// 4 single floats when other as 2 double precision floats. This
	// field is used to describe such data format whenever possible.
	uint16_t data_type;
};

struct ira_addressing {
	// Type of addressing.
	enum ira_addressing_type addressing_type;
	// Segment register used with addressing.
	struct ira_segment_selector segment_selector;
	// Size of the direct address (ESA).
	enum ira_address_size address_size;
	// Value of the direct address.
	union ira_address_value address_value;
	// Implicit register addressing.
	struct ira_register address_register;
	// TODO: Przniesc to gdzies, to nie wielkosc adresu tylko
	// wiekosc danych jakie trafia pod ten adres, trzeba znalezc na to lepsze miejsce.
	uint16_t size_directive;
	// ModRM addressing.
	struct ira_mod_rm_addressing mod_rm;
};

struct ira_instruction_operand {
	// Type of operand.
	enum ira_operand_type operand_type;
	// Access mode.
	enum ira_access_mode access_mode;
	// Place for immediate data.
	struct ira_immediate_data immediate;
	// Addressing.
	struct ira_addressing addressing;
	// Register.
	struct ira_register reg;
};

struct ira_instruction_prefix {
	/* Prefix itself. */
	uint8_t prefix;
	/* Type of prefix, see enumeration above. */
	uint8_t prefix_type;
	/* 1 if prefix can be treated as mandatory one. */
	uint8_t mandatory_prefix;
};

struct ira_instruction_condition {
	// 1 - If instruction is conditional one.
	int8_t is_conditional;
	// 1 - If this is a negation of the condition.
	int8_t is_condition_negation;
	// Condition type of the instruction.
	enum ira_condition_type condition_type;
};


// TODO: Pomyslec and typami instrunkcji CONDITIONAL/ MOVE itd.
struct ira_disassemble_result {
	/* Disassemblation result code. */
	enum ira_result_code code;
	/* Mnemonic */
	char *mnemonic;
	// TODO: Moze to przeniesc doc egos w rodzaju instruction details.?
	// Condition used by conditional instructions.
	struct ira_instruction_condition condition;
	// Number of prefixes.
	uint8_t prefixes_count;
	// Prefixes.
	struct ira_instruction_prefix prefixes[_IRA_PREFIXES_COUNT];
	// Opcode bytes without mandatory prefixes.
	uint8_t opcodes[3];
	// Number of opcode bytes.
	uint8_t opcodes_count;
	// Primary opcode byte.
	uint8_t primary_opcode_index;
	// REX prefix.
	n_byte rex;
	// Instruction size in bytes.
	uint8_t instruction_size;
	// Instruction size is limited to 15 bytes.
	uint8_t instruction_code[15];
	// Disassembled operands.
	struct ira_instruction_operand operands[_IRA_OPERANDS_COUNT];
};

enum ira_result_code ira_init(void);

void ira_disassemble(struct ira_disassemble_info *info, struct ira_disassemble_result *result);

void ira_deinit(void);

#endif // IRA_H_INCLUDED
