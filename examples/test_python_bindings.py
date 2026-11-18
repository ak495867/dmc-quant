import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "python")))
import dmc_quant as dq

def main():
    print("Testing Demonic C Quant Python Bindings...")
    call_px = dq.bs_call(100.0, 100.0, 1.0, 0.05, 0.20)
    print(f"BS Call (S=100, K=100, T=1, r=0.05, sigma=0.20): ${call_px:.4f}")
    assert 10.40 <= call_px <= 10.55, f"Invalid call price: {call_px}"

    bond_px = dq.fi_bond_price(100.0, 0.05, 0.05, 5.0, 2)
    print(f"Bond Par Price (5Y 5% Coupon @ 5% YTM): ${bond_px:.2f}")
    assert 99.9 <= bond_px <= 100.1, f"Invalid bond price: {bond_px}"

    dex_out = dq.amm_swap_out(10.0, 1000.0, 2000.0, 30)
    print(f"AMM Swap 10 IN -> OUT: {dex_out:.4f}")
    assert 19.5 <= dex_out <= 19.9, f"Invalid AMM out: {dex_out}"

    pvar = dq.risk_var(1000000.0, 0.02, 0.95)
    print(f"95% Daily VaR ($1M Portfolio, 2% daily vol): ${pvar:,.2f}")
    assert pvar > 0, "VaR must be positive"

    print("ALL PYTHON BINDING TESTS PASSED!")

if __name__ == "__main__":
    main()
