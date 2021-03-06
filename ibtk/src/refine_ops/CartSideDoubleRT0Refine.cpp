// ---------------------------------------------------------------------
//
// Copyright (c) 2019 - 2021 by the IBAMR developers
// All rights reserved.
//
// This file is part of IBAMR.
//
// IBAMR is free software and is distributed under the 3-clause BSD
// license. The full text of the license can be found in the file
// COPYRIGHT at the top level directory of IBAMR.
//
// ---------------------------------------------------------------------

/////////////////////////////// INCLUDES /////////////////////////////////////

#include "ibtk/CartSideDoubleRT0Refine.h"

#include "Box.h"
#include "SideVariable.h"
#include "tbox/Pointer.h"

#include <string>

#include "ibtk/namespaces.h" // IWYU pragma: keep

namespace SAMRAI
{
namespace hier
{
template <int DIM>
class Variable;
} // namespace hier
} // namespace SAMRAI

// FORTRAN ROUTINES
#if (NDIM == 2)
#define CART_SIDE_RT0_REFINE_FC IBTK_FC_FUNC_(cart_side_rt0_refine2d, CART_SIDE_RT0_REFINE2D)
#endif
#if (NDIM == 3)
#define CART_SIDE_RT0_REFINE_FC IBTK_FC_FUNC_(cart_side_rt0_refine3d, CART_SIDE_RT0_REFINE3D)
#endif

// Function interfaces
extern "C"
{
    void CART_SIDE_RT0_REFINE_FC(
#if (NDIM == 2)
        double*,
        double*,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const double*,
        const double*,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
#endif
#if (NDIM == 3)
        double*,
        double*,
        double*,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const double*,
        const double*,
        const double*,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
        const int&,
#endif
        const int*);
}

/////////////////////////////// NAMESPACE ////////////////////////////////////

namespace IBTK
{
/////////////////////////////// STATIC ///////////////////////////////////////

const std::string CartSideDoubleRT0Refine::s_op_name = "RT0_REFINE";

namespace
{
static const int REFINE_OP_PRIORITY = 0;
static const int REFINE_OP_STENCIL_WIDTH = 1;
} // namespace

/////////////////////////////// PUBLIC ///////////////////////////////////////

bool
CartSideDoubleRT0Refine::findRefineOperator(const Pointer<Variable<NDIM> >& var, const std::string& op_name) const
{
    const Pointer<SideVariable<NDIM, double> > sc_var = var;
    return (sc_var && op_name == s_op_name);
} // findRefineOperator

const std::string&
CartSideDoubleRT0Refine::getOperatorName() const
{
    return s_op_name;
} // getOperatorName

int
CartSideDoubleRT0Refine::getOperatorPriority() const
{
    return REFINE_OP_PRIORITY;
} // getOperatorPriority

IntVector<NDIM>
CartSideDoubleRT0Refine::getStencilWidth() const
{
    return REFINE_OP_STENCIL_WIDTH;
} // getStencilWidth

void
CartSideDoubleRT0Refine::refine(Patch<NDIM>& fine,
                                const Patch<NDIM>& coarse,
                                const int dst_component,
                                const int src_component,
                                const Box<NDIM>& fine_box,
                                const IntVector<NDIM>& ratio) const
{
    // Get the patch data.
    Pointer<SideData<NDIM, double> > fdata = fine.getPatchData(dst_component);
    Pointer<SideData<NDIM, double> > cdata = coarse.getPatchData(src_component);
#if !defined(NDEBUG)
    TBOX_ASSERT(fdata);
    TBOX_ASSERT(cdata);
    TBOX_ASSERT(fdata->getDepth() == cdata->getDepth());
#endif
    const int data_depth = fdata->getDepth();

    const Box<NDIM>& fdata_box = fdata->getBox();
    const int fdata_gcw = fdata->getGhostCellWidth().max();
#if !defined(NDEBUG)
    TBOX_ASSERT(fdata_gcw == fdata->getGhostCellWidth().min());
#endif

    const Box<NDIM>& cdata_box = cdata->getBox();
    const int cdata_gcw = cdata->getGhostCellWidth().max();
#if !defined(NDEBUG)
    TBOX_ASSERT(cdata_gcw == cdata->getGhostCellWidth().min());
#endif

    // Refine the data.
    for (int depth = 0; depth < data_depth; ++depth)
    {
        CART_SIDE_RT0_REFINE_FC(
#if (NDIM == 2)
            fdata->getPointer(0, depth),
            fdata->getPointer(1, depth),
            fdata_gcw,
            fdata_box.lower()(0),
            fdata_box.upper()(0),
            fdata_box.lower()(1),
            fdata_box.upper()(1),
            cdata->getPointer(0, depth),
            cdata->getPointer(1, depth),
            cdata_gcw,
            cdata_box.lower()(0),
            cdata_box.upper()(0),
            cdata_box.lower()(1),
            cdata_box.upper()(1),
            fine_box.lower()(0),
            fine_box.upper()(0),
            fine_box.lower()(1),
            fine_box.upper()(1),
#endif
#if (NDIM == 3)
            fdata->getPointer(0, depth),
            fdata->getPointer(1, depth),
            fdata->getPointer(2, depth),
            fdata_gcw,
            fdata_box.lower()(0),
            fdata_box.upper()(0),
            fdata_box.lower()(1),
            fdata_box.upper()(1),
            fdata_box.lower()(2),
            fdata_box.upper()(2),
            cdata->getPointer(0, depth),
            cdata->getPointer(1, depth),
            cdata->getPointer(2, depth),
            cdata_gcw,
            cdata_box.lower()(0),
            cdata_box.upper()(0),
            cdata_box.lower()(1),
            cdata_box.upper()(1),
            cdata_box.lower()(2),
            cdata_box.upper()(2),
            fine_box.lower()(0),
            fine_box.upper()(0),
            fine_box.lower()(1),
            fine_box.upper()(1),
            fine_box.lower()(2),
            fine_box.upper()(2),
#endif
            ratio);
    }
    return;
} // refine

/////////////////////////////// PROTECTED ////////////////////////////////////

/////////////////////////////// PRIVATE //////////////////////////////////////

/////////////////////////////// NAMESPACE ////////////////////////////////////

} // namespace IBTK

//////////////////////////////////////////////////////////////////////////////
