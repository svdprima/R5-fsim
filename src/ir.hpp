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
    uint32_t imm_2;
    void (*cmd) (const Instruction*, const Instruction*, HartState*);
    const char* command_name;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t rd_2;
    uint8_t rs1_2;
    uint8_t rs2_2;
    bool    BBEnd;
public:
    InstrType type;
    Instruction () : imm(0), imm_2(0), rd(0), rs1(0), rs2(0), rd_2(0), rs1_2(0), rs2_2(0), BBEnd(true), type(InstrType::Undefined)
    {
    }
    inline void ExecCommand (const Instruction* first_instr, HartState* hart_state) const
    {
        cmd (first_instr, this, hart_state);
    }
    inline void SetRd (uint8_t RD)
    {
        rd = RD;
    }
    inline void SetRd_2 (uint8_t RD_2)
    {
        rd_2 = RD_2;
    }
    inline void SetRs1 (uint8_t RS1)
    {
        rs1 = RS1;
    }
    inline void SetRs1_2 (uint8_t RS1_2)
    {
        rs1_2 = RS1_2;
    }
    inline void SetRs2 (uint8_t RS2)
    {
        rs2 = RS2;
    }
    inline void SetRs2_2 (uint8_t RS2_2)
    {
        rs2_2 = RS2_2;
    }
    inline void SetImm_2 (uint32_t _imm_2)
    {
        imm_2 = _imm_2;
    }
    inline void SetImm (uint32_t _imm)
    {
        imm = _imm;
    }
    inline void SetCommand (const char* c_name, void (*command) (const Instruction*, const Instruction*, HartState*))
    {
        command_name = c_name;
        cmd = command;
    }
    inline void SetBBEnd(bool value)
    {
        BBEnd = value;
    }
    void PrintInstr (const bool is_verbose) const
    {
        printf ("%s\n", command_name);
        if (is_verbose)
        {
            switch (type)
            {
                case InstrType::RType:
                    printf ("RType\n");
                    printf ("rd     : %u\n", rd);
                    printf ("rs1    : %u\n", rs1);
                    printf ("rs2    : %u\n", rs2);
                    break;
                case InstrType::IType:
                    printf ("IType\n");
                    printf ("rd     : %u\n", rd);
                    printf ("rs1    : %u\n", rs1);
                    printf ("imm    : %x\n", imm);
                    break;
                case InstrType::SType:
                    printf ("SType\n");
                    printf ("rs1    : %u\n", rs1);
                    printf ("rs2    : %u\n", rs2);
                    printf ("imm    : %x\n", imm);
                    break;
                case InstrType::BType:
                    printf ("BType\n");
                    printf ("rs1    : %u\n", rs1);
                    printf ("rs2    : %u\n", rs2);
                    printf ("imm    : %x\n", imm);
                    break;
                case InstrType::UType:
                    printf ("UType\n");
                    printf ("rd     : %u\n", rd);
                    printf ("imm    : %x\n", imm);
                    break;
                case InstrType::JType:
                    printf ("JType\n");
                    printf ("rd     : %u\n", rd);
                    printf ("imm    : %x\n", imm);
                    break;
                default:
                    printf ("Type is undefined\n");
            }
            printf ("\n");
        }
    }    
    inline uint8_t GetRd () const
    {
        return rd;
    }
    inline uint8_t GetRd_2 () const
    {
        return rd_2;
    }
    inline uint8_t GetRs1 () const
    {
        return rs1;
    }
    inline uint8_t GetRs1_2 () const
    {
        return rs1_2;
    }
    inline uint8_t GetRs2 () const
    {
        return rs2;
    }
    inline uint8_t GetRs2_2 () const
    {
        return rs2_2;
    }
    inline uint32_t GetImm () const
    {
        return imm;
    }
    inline uint32_t GetImm_2 () const
    {
        return imm_2;
    }
    inline bool GetBBEnd () const
    {
        return BBEnd;
    }
    inline void (*GetCmd())(const Instruction*, const Instruction*, HartState*)
    {
        return cmd;
    }
};

#endif
