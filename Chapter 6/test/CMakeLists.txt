# Add Ch 6 regression tests.
configure_lit_site_cfg(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
    MAIN_CONFIG
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py)

add_lit_testsuite(check-ch6
  "Running the Chapter 6 regression tests"
    ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ch6_read_ir)
