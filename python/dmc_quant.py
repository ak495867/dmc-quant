import ctypes
import os
import sys

_dll_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "lib", "dmc_quant.dll"))
if not os.path.exists(_dll_path):
    _dll_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "lib", "libdmc_quant.so"))
if not os.path.exists(_dll_path):
    _dll_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "lib", "libdmc_quant.dylib"))

_lib = ctypes.CDLL(_dll_path)

# Derivative Pricing
_lib.bs_call.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.bs_call.restype = ctypes.c_float

_lib.bs_put.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.bs_put.restype = ctypes.c_float

_lib.bs_delta_call.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.bs_delta_call.restype = ctypes.c_float

_lib.bs_gamma.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.bs_gamma.restype = ctypes.c_float

_lib.bs_vega.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.bs_vega.restype = ctypes.c_float

_lib.bs_implied_vol.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int]
_lib.bs_implied_vol.restype = ctypes.c_float

# LOB Engine
_lib.lob_create.argtypes = [ctypes.c_int]
_lib.lob_create.restype = ctypes.c_int

_lib.lob_add_limit.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.lob_add_limit.restype = ctypes.c_int

_lib.lob_add_market.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.lob_add_market.restype = ctypes.c_int

_lib.lob_best_bid.argtypes = [ctypes.c_int]
_lib.lob_best_bid.restype = ctypes.c_int

_lib.lob_best_ask.argtypes = [ctypes.c_int]
_lib.lob_best_ask.restype = ctypes.c_int

# Fixed Income
_lib.fi_bond_price.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int]
_lib.fi_bond_price.restype = ctypes.c_float

_lib.fi_modified_duration.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int]
_lib.fi_modified_duration.restype = ctypes.c_float

_lib.fi_dv01.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int]
_lib.fi_dv01.restype = ctypes.c_float

# Microstructure
_lib.micro_order_book_imbalance.argtypes = [ctypes.c_int, ctypes.c_int]
_lib.micro_order_book_imbalance.restype = ctypes.c_float

_lib.micro_price.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_int, ctypes.c_int]
_lib.micro_price.restype = ctypes.c_float

# AMM
_lib.amm_get_amount_out.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int]
_lib.amm_get_amount_out.restype = ctypes.c_float

_lib.amm_impermanent_loss.argtypes = [ctypes.c_float]
_lib.amm_impermanent_loss.restype = ctypes.c_float

# Risk
_lib.risk_parametric_var.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.risk_parametric_var.restype = ctypes.c_float

_lib.risk_sharpe_ratio.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
_lib.risk_sharpe_ratio.restype = ctypes.c_float

def bs_call(s: float, k: float, t: float, r: float, sigma: float) -> float:
    return _lib.bs_call(s, k, t, r, sigma)

def bs_put(s: float, k: float, t: float, r: float, sigma: float) -> float:
    return _lib.bs_put(s, k, t, r, sigma)

def bs_delta(s: float, k: float, t: float, r: float, sigma: float) -> float:
    return _lib.bs_delta_call(s, k, t, r, sigma)

def fi_bond_price(face: float, coupon: float, ytm: float, years: float, freq: int = 2) -> float:
    return _lib.fi_bond_price(face, coupon, ytm, years, freq)

def fi_modified_duration(face: float, coupon: float, ytm: float, years: float, freq: int = 2) -> float:
    return _lib.fi_modified_duration(face, coupon, ytm, years, freq)

def amm_swap_out(amount_in: float, reserve_in: float, reserve_out: float, fee_bps: int = 30) -> float:
    return _lib.amm_get_amount_out(amount_in, reserve_in, reserve_out, fee_bps)

def risk_var(portfolio_value: float, volatility: float, confidence: float = 0.95) -> float:
    return _lib.risk_parametric_var(portfolio_value, volatility, confidence)
