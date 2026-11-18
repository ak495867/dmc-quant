# dmc-quant Usage Guide & API Cookbook

Comprehensive recipes and copy-paste examples for every quantitative sub-library in `dmc-quant`.

---

## 1. Central Limit Order Book & Level-2 Depth (`lob.dmc`)

```dmc
import "lob";

fn example_lob() -> int {
    let book: int = lob_create(0);

    // Add Limit Bids & Asks
    lob_add_limit(book, 101, 1, 15000, 100); // Buy 100 @ $150.00
    lob_add_limit(book, 102, 2, 15020, 150); // Sell 150 @ $150.20

    let bb: int = lob_best_bid(book);
    let ba: int = lob_best_ask(book);
    let spread: int = lob_spread(book);

    // Cross with a Market Order (Buy 50)
    let filled: int = lob_add_market(book, 1, 50);

    // Query Level-2 Market Depth
    var l0_px: int = 0;
    var l0_qty: int = 0;
    lob_level2_depth(book, 2, 0, &l0_px, &l0_qty);

    return 0;
}
```

---

## 2. Derivative Pricing & 256-Bit SIMD Batching (`pricing.dmc`)

```dmc
import "pricing";

fn example_pricing() -> int {
    // Analytical Black-Scholes Call & Put
    let call_px: float = bs_call(100.0, 100.0, 1.0, 0.05, 0.20);
    let put_px: float = bs_put(100.0, 100.0, 1.0, 0.05, 0.20);

    // Greeks
    let delta: float = bs_delta_call(100.0, 100.0, 1.0, 0.05, 0.20);
    let gamma: float = bs_gamma(100.0, 100.0, 1.0, 0.05, 0.20);
    let vega: float = bs_vega(100.0, 100.0, 1.0, 0.05, 0.20);

    // American Option with Early Exercise (Binomial Lattice)
    let am_put: float = crr_american_option(100.0, 100.0, 1.0, 0.05, 0.20, 50, 0);

    // 8-Wide Batch SIMD Pricing (Processes 8 Options Simultaneously)
    let s_vec: f32x8 = f32x8(90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0);
    let k_vec: f32x8 = f32x8(100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0);
    let t_vec: f32x8 = f32x8(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    let r_vec: f32x8 = f32x8(0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05);
    let vol_vec: f32x8 = f32x8(0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20);

    let batch_calls: f32x8 = bs_batch_call8(s_vec, k_vec, t_vec, r_vec, vol_vec);

    return 0;
}
```

---

## 3. Fixed Income, Yield Curves & Duration (`fixed_income.dmc`)

```dmc
import "fixed_income";

fn example_fixed_income() -> int {
    // 10-Year Treasury Bond, 4.5% Coupon, 4.2% Yield, Semi-Annual
    let price: float = fi_bond_price(100.0, 0.045, 0.042, 10.0, 2);
    let mod_duration: float = fi_modified_duration(100.0, 0.045, 0.042, 10.0, 2);
    let dv01: float = fi_dv01(100.0, 0.045, 0.042, 10.0, 2);

    // Yield to Maturity Solver
    let ytm: float = fi_bond_ytm(100.0, 0.045, price, 10.0, 2);

    // Forward Rates: 1-Year Spot 4% vs 2-Year Spot 5%
    let fwd_rate: float = fi_forward_rate(0.04, 1.0, 0.05, 2.0); // 6.0%

    return 0;
}
```

---

## 4. Market Microstructure & Flow Toxicity (`microstructure.dmc`)

```dmc
import "microstructure";

fn example_microstructure() -> int {
    // Order Book Imbalance (OBI)
    let obi: float = micro_order_book_imbalance(350, 150); // +0.40

    // Volume-Weighted Micro-Price
    let fair_px: float = micro_price(100.0, 100.20, 350, 150);

    // Volume-Synchronized Probability of Toxicity (VPIN)
    var buys: [float; 3] = [500.0, 400.0, 600.0];
    var sells: [float; 3] = [500.0, 600.0, 400.0];
    let vpin: float = micro_vpin(&buys[0], &sells[0], 3, 1000.0);

    return 0;
}
```

---

## 5. Automated Market Maker & DeFi Math (`amm.dmc`)

```dmc
import "amm";

fn example_amm() -> int {
    // Pool: 1,000 ETH / 2,000,000 USDC (Spot = $2,000)
    let spot: float = amm_spot_price(1000.0, 2000000.0);

    // Swap 10 ETH into USDC with 0.30% fee (30 bps)
    let usdc_out: float = amm_get_amount_out(10.0, 1000.0, 2000000.0, 30);
    let slippage: float = amm_slippage_bps(10.0, 1000.0, 2000000.0, 30);

    // Impermanent Loss for a 50% price change (k = 1.5)
    let il: float = amm_impermanent_loss(1.50); // -2.02%

    return 0;
}
```

---

## 6. Financial Protocols: FIX 4.4 & ITCH 5.0 (`fix.dmc`)

```dmc
import "fix";

fn example_fix() -> int {
    // Zero-overhead FIX 4.4 New Order Single serialization
    let msg: string = fix_build_new_order_single("ORD101", "MSFT", 1, 310.50, 100, "QUANT_DESK", "EXCHANGE");

    // Zero-allocation field extraction
    let side: int = fix_fast_get_int(msg, 54);
    let qty: int = fix_fast_get_int(msg, 38);
    let px: float = fix_fast_get_float(msg, 44);

    // Checksum verification
    let valid: int = fix_validate_checksum(msg);

    return 0;
}
```

---

## 7. Python Integration via C-Bindings

```python
import dmc_quant as dq

# Call option pricing
call_px = dq.bs_call(100.0, 100.0, 1.0, 0.05, 0.20)

# Treasury Bond pricing
bond_px = dq.fi_bond_price(100.0, 0.05, 0.05, 10.0, 2)

# AMM DEX output
dex_out = dq.amm_swap_out(10.0, 1000.0, 2000.0, 30)

# 95% Daily VaR
var_loss = dq.risk_var(1_000_000.0, 0.02, 0.95)
```
