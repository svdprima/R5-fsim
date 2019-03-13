#ifndef IR_HPP
#define IR_HPP

enum class InstrType: uint8_t
{
    Undefined,
    RType,
    IType,
    SType,
    BType,  
    UType,
    JType
};

enum class Oppcodes: uint8_t
{
    LUI      = 0b0110111,
    AUIPC    = 0b0010111,
    JAL      = 0b1101111,
    JALR     = 0b1100111,
    BRANCH   = 0b1100011,
    LOAD     = 0b0000011,
    STORE    = 0b0100011,
    OPP_IMM  = 0b0010011,
    OP       = 0b0110011,
    MISC_MEM = 0b0001111,
    SYSTEM   = 0b1110011,
    UNINIT   = 0b11  
};

struct OppcodeDescr
{
    Oppcodes oppcode;
    InstrType type;
};

const OppcodeDescr OppcodeType[] = 
{
    {Oppcodes::LUI,     InstrType::UType},
    {Oppcodes::AUIPC,   InstrType::UType},
    {Oppcodes::JAL,     InstrType::JType},
    {Oppcodes::JALR,    InstrType::IType},
    {Oppcodes::BRANCH,  InstrType::BType},
    {Oppcodes::LOAD,    InstrType::IType},
    {Oppcodes::STORE,   InstrType::SType},
    {Oppcodes::OPP_IMM, InstrType::IType},
    {Oppcodes::OP,      InstrType::RType},
    {Oppcodes::MISC_MEM,InstrType::IType},
    {Oppcodes::SYSTEM,  InstrType::IType}
};



class Instruction
{
private:
    uint32_t imm;
    void (*cmd) (const Instruction*, const Instruction*, HartState*);
    const char* command_name;
    uint8_t oppcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    bool    BBEnd;
public:
    InstrType type;
    Instruction () : imm(0), oppcode(0), rd(0), funct3(0), rs1(0), rs2(0), funct7(0), BBEnd(true), type(InstrType::Undefined)
    {
    }
    void ExecCommand (const Instruction* first_instr, HartState* hart_state) const;
    void SetOppcode (uint8_t oppc);
    void SetRd (uint8_t RD);
    void SetFunct3 (uint8_t f3);
    void SetRs1 (uint8_t RS1);
    void SetRs2 (uint8_t RS2);
    void SetFunct7 (uint8_t f7);
    void SetImm (uint32_t _imm);
    void SetCommand (const char* c_name, void (*command) (const Instruction*, const Instruction*, HartState*))
    {
        command_name = c_name;
        cmd = command;
    }
    void SetBBEnd(bool value)
    {
        BBEnd = value;
    }
    void PrintInstr (const bool is_verbose) const;

    inline uint8_t GetOppcode () const
    {
        return oppcode;
    }

    inline uint8_t GetRd () const
    {
        return rd;
    }

    inline uint8_t GetFunct3 () const
    {
        return funct3;
    }

    inline uint8_t GetRs1 () const

    {
        return rs1;
    }

    inline uint8_t GetRs2 () const
    {
        return rs2;
    }

    inline uint8_t GetFunct7 () const
    {
        return funct7;
    }

    inline uint32_t GetImm () const
    {
        return imm;
    }
    inline bool GetBBEnd () const
    {
        return BBEnd;
    }
};

#endif