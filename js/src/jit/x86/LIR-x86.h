/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jit_x86_LIR_x86_h
#define jit_x86_LIR_x86_h

namespace js {
namespace jit {

class LBox : public LInstructionHelper<2, 1, 0>
{
    MIRType type_;

  public:
    LIR_HEADER(Box);

    LBox(const LAllocation &in_payload, MIRType type)
      : type_(type)
    {
        setOperand(0, in_payload);
    }

    MIRType type() const {
        return type_;
    }
};

class LBoxFloatingPoint : public LInstructionHelper<2, 1, 1>
{
    MIRType type_;

  public:
    LIR_HEADER(BoxFloatingPoint);

    LBoxFloatingPoint(const LAllocation &in, const LDefinition &temp, MIRType type)
      : type_(type)
    {
        JS_ASSERT(IsFloatingPointType(type));
        setOperand(0, in);
        setTemp(0, temp);
    }

    MIRType type() const {
        return type_;
    }
};

class LUnbox : public LInstructionHelper<1, 2, 0>
{
  public:
    LIR_HEADER(Unbox);

    MUnbox *mir() const {
        return mir_->toUnbox();
    }
    const LAllocation *payload() {
        return getOperand(0);
    }
    const LAllocation *type() {
        return getOperand(1);
    }
};

class LUnboxFloatingPoint : public LInstructionHelper<1, 2, 0>
{
    MIRType type_;

  public:
    LIR_HEADER(UnboxFloatingPoint);

    static const size_t Input = 0;

    LUnboxFloatingPoint(MIRType type)
      : type_(type)
    { }

    MUnbox *mir() const {
        return mir_->toUnbox();
    }

    MIRType type() const {
        return type_;
    }
};

// Convert a 32-bit unsigned integer to a double.
class LUInt32ToDouble : public LInstructionHelper<1, 1, 1>
{
  public:
    LIR_HEADER(UInt32ToDouble)

    LUInt32ToDouble(const LAllocation &input, const LDefinition &temp) {
        setOperand(0, input);
        setTemp(0, temp);
    }
    const LDefinition *temp() {
        return getTemp(0);
    }
};

class LAsmJSLoadFuncPtr : public LInstructionHelper<1, 1, 0>
{
  public:
    LIR_HEADER(AsmJSLoadFuncPtr);
    LAsmJSLoadFuncPtr(const LAllocation &index) {
        setOperand(0, index);
    }
    MAsmJSLoadFuncPtr *mir() const {
        return mir_->toAsmJSLoadFuncPtr();
    }
    const LAllocation *index() {
        return getOperand(0);
    }
};

} // namespace jit
} // namespace js

#endif /* jit_x86_LIR_x86_h */
