###  CMakeLists.txt ---

#  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
#       Date: 2009-11-11
#
#  Copyright (C) 2009 Université Joseph Fourier (Grenoble I)
#
# Distributed under the GPL(GNU Public License):
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#
set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL TRUE)
feelpp_add_application(beam SRCS beam.cpp LABELS doc)
feelpp_add_application(stvenant_kirchhoff SRCS stvenant_kirchhoff.cpp LABELS doc)
feelpp_add_application(stvenant_kirchhoff2 SRCS stvenant_kirchhoff2.cpp LABELS doc CFG stvenant_kirchhoff2.cfg)
feelpp_add_application(axi_1D SRCS axi_1D.cpp LABELS doc)
feelpp_add_application(linelaxi SRCS linelaxi.cpp LABELS doc)
