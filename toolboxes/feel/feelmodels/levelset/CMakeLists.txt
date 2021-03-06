
# geo order 1 (non-periodic)
foreach(_DIM 2 3)
  math(EXPR _PHI_ORDER '${FEELPP_INSTANTIATION_ORDER_MAX}-1')
  feelpp_max( MAX_ORDER 1 ${_PHI_ORDER})
  message(STATUS "[feelpp] LEVELSET ${_DIM}D PNG1 N=1..${MAX_ORDER}")
  foreach( _PHI_ORDER RANGE 1 ${MAX_ORDER} )
      genLibLevelset(
          DIM     ${_DIM}
          LEVELSET_ORDER ${_PHI_ORDER}
          GEO_ORDER 1 
          )
  set(FEELPP_MODELS_LIBRARIES_LEVELSET  ${FEELPP_MODELS_LIBRARIES_LEVELSET} ${LEVELSET_LIB_NAME}  )
  endforeach()
endforeach()

## isoparametric (non-periodic)
#foreach(_DIM 2 3)
  #math(EXPR _PHI_ORDER '${FEELPP_INSTANTIATION_ORDER_MAX}-1')
  #feelpp_min( MAX_ORDER ${FEELPP_MESH_MAX_ORDER} ${_PHI_ORDER})
  #message(STATUS "[feelpp] LEVELSET ${_DIM}D PNGN N=2..${MAX_ORDER}")
  #foreach( _PHI_ORDER RANGE 2 ${MAX_ORDER} )
      #genLibLevelset(
      #DIM     ${_DIM}
      #PHI_ORDER ${_PHI_ORDER}
      #GEO_ORDER ${_PHI_ORDER}
      #)
  #set(FEELPP_MODELS_LIBRARIES_LEVELSET  ${FEELPP_MODELS_LIBRARIES_LEVELSET} ${LEVELSET_LIB_NAME} )
  #endforeach()
#endforeach()

add_library(feelpp_toolbox_levelset_lib SHARED liblevelset.cpp )
target_link_libraries(feelpp_toolbox_levelset_lib ${FEELPP_MODELS_LIBRARIES_LEVELSET})
set_property(TARGET feelpp_toolbox_levelset_lib PROPERTY MACOSX_RPATH ON)
install(TARGETS feelpp_toolbox_levelset_lib DESTINATION lib/ COMPONENT Libs EXPORT feelpp-toolboxes-targets)

FILE(GLOB files "*.hpp")
INSTALL(FILES ${files} DESTINATION include/feelpp/toolboxes/feel/feelmodels/levelset COMPONENT Devel)
