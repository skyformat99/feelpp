/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t  -*-

 This file is part of the Feel++ library

 Author(s): Vincent Chabannes <vincent.chabannes@feelpp.org>
 Date: 22 Feb 2018

 Copyright (C) 2018 Feel++ Consortium

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <feel/feelmodels/modelexpression.hpp>

namespace Feel {

void
ModelExpression::setExpr( std::string const& key, pt::ptree const& p, WorldComm const& worldComm, std::string const& directoryLibExpr )
{
    if( boost::optional<double> itvald = p.get_optional<double>( key ) )
    {
        double val = *itvald;
        VLOG(1) << "expr at key " << key << " is constant : " << val;
        this->setValue( val );
    }
    else if( boost::optional<std::string> itvals = p.get_optional<std::string>( key ) )
    {
        std::string feelExprString = *itvals;
        auto parseExpr = GiNaC::parse( feelExprString );
        auto const& exprSymbols = parseExpr.second;
        auto ginacEvalm = parseExpr.first.evalm();

        bool isLst = GiNaC::is_a<GiNaC::lst>( ginacEvalm );
        int nComp = 1;
        if ( isLst )
            nComp = ginacEvalm.nops();

        if ( nComp == 1 && ( exprSymbols.empty() /*|| ( exprSymbols.size() == 1 && exprSymbols[0].get_name() == "0" )*/ ) )
        {
            std::string stringCstExpr = ( isLst )? str( ginacEvalm.op(0) ) :str( ginacEvalm );
            double val = 0;
            try
            {
                val = std::stod( stringCstExpr );
            }
            catch (std::invalid_argument& err)
            {
                CHECK( false ) << "cast fail from expr to double\n";
            }
            VLOG(1) << "expr at key " << key <<" is const from expr=" << val;
            this->setValue( val );
        }
        else
        {
            VLOG(1) << "expr at key " << key << " build symbolic expr with nComp=" << nComp;
            if ( nComp == 1 )
                this->setExprScalar( Feel::vf::expr<expr_order>( feelExprString,"",worldComm,directoryLibExpr ) );
            else if ( nComp == 2 )
                this->setExprVectorial2( Feel::vf::expr<2,1,expr_order>( feelExprString,"",worldComm,directoryLibExpr ) );
            else if ( nComp == 3 )
                this->setExprVectorial3( Feel::vf::expr<3,1,expr_order>( feelExprString,"",worldComm,directoryLibExpr ) );
            else if ( nComp == 4 )
                this->setExprMatrix22( Feel::vf::expr<2,2,expr_order>( feelExprString,"",worldComm,directoryLibExpr ) );
            else if ( nComp == 9 )
                this->setExprMatrix33( Feel::vf::expr<3,3,expr_order>( feelExprString,"",worldComm,directoryLibExpr ) );
        }
    }
}


} // namespace Feel
