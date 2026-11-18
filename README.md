# dmc-quant

A high-performance quantitative finance, algorithmic trading, and portfolio engineering toolkit written in Demonic C.

This multi-module monorepo provides sub-microsecond trading primitives, zero-allocation financial protocol parsers, derivative pricing models with 256-bit SIMD acceleration, fixed income yield math, market microstructure toxicity metrics, decentralized AMM math, and native C-interop dynamic shared library exports.

---

## Architecture & Modules

| Module | Source File | Capabilities & Features |
|---|---|---|
| **LOB Engine** | `src/lob.dmc` | Strict price-time priority (FIFO) limit order book (1,024-order capacity), market orders, cancellation, BBO, spread, mid-price, VWAP, and Level-2 market depth extraction (`lob_level2_depth`). |
| **Option Pricing** | `src/pricing.dmc` | Black-Scholes analytical formulas, Greeks ($\Delta, \Gamma, \mathcal{V}, \Theta, \rho$), fast polynomial CDF approximation (`bs_fast_cnd`), 8-wide batch SIMD option pricing (`bs_batch_call8`, `bs_batch_put8`), Cox-Ross-Rubinstein American binomial tree (`crr_american_option`), Marsaglia Xorshift Monte Carlo (`bs_monte_carlo_fast`), and SIMD payoffs (`f32x8`). |
| **Technical Time-Series** | `src/timeseries.dmc` | Streaming statistical metrics: SMA, EMA, 14-period RSI, MACD lines, Bollinger Bands, rolling volatility, skewness, kurtosis, covariance, correlation, J.P. Morgan RiskMetrics EWMA volatility (`ts_ewma_volatility`), autocorrelation, rolling Z-score, and SIMD reductions (`ts_simd_dot`, `ts_simd_sum`). |
| **Financial Protocols** | `src/fix.dmc` | FIX 4.4 message serializer & checksum validator, zero-allocation fast field parsers (`fix_fast_get_int`, `fix_fast_get_float`), and NASDAQ ITCH 5.0 binary order book packet encoder/decoder (`itch_parse_add_order`). |
| **Fixed Income & Rates** | `src/fixed_income.dmc` | Bond pricing from yield, Newton-Raphson Yield to Maturity (YTM) solver, Macaulay & Modified Duration, Bond Convexity, DV01/PV01, zero-coupon discount factor curves, and forward rates. |
| **Market Microstructure** | `src/microstructure.dmc` | Volume-Synchronized Probability of Toxicity (`micro_vpin`), Order Book Imbalance (`micro_order_book_imbalance`), Volume-Weighted Micro-Price (`micro_price`), Kyle's Lambda price impact coefficient, Amihud illiquidity ratio, Roll model effective spread, and Realized Spread. |
| **DeFi & AMM Math** | `src/amm.dmc` | Constant Product Automated Market Maker output/input with fee basis points, spot price, execution price slippage, Impermanent Loss calculator (`amm_impermanent_loss`), 2-pool optimal arbitrage trade sizing, and Uniswap v3 tick-to-price conversion. |
| **Portfolio Risk Engine** | `src/risk.dmc` | Historical Value at Risk (VaR), Parametric VaR, Conditional VaR (Expected Shortfall), Sharpe Ratio, Sortino Ratio, Maximum Drawdown, Calmar Ratio, market Beta, Omega ratio (`risk_omega_ratio`), and tail risk ratio (`risk_tail_ratio`). |
| **Portfolio Optimization** | `src/portfolio.dmc` | Markowitz 2-asset minimum variance, tangency (maximum Sharpe ratio), risk parity (inverse volatility), portfolio variance/return ($w^T \Sigma w$, $w^T R$), capital rebalancing share calculator, and Compound Annual Growth Rate (`port_cagr`). |
| **Algorithmic Execution** | `src/execution.dmc` | TWAP slice distribution, VWAP volume-weighted slicing, POV (percentage-of-volume) participation slicing, implementation shortfall, and slippage in basis points. |
| **Alpha Factors & ML** | `src/ml_factors.dmc` | Cross-sectional Z-score standardization, quantile winsorization, Ornstein-Uhlenbeck mean-reversion half-life, Information Coefficient (IC), percentile ranking (`factor_rank`), and Spearman rank correlation (`factor_spearman_ic`). |
| **SIMD Linear Algebra** | `src/simd_matrix.dmc` | 256-bit SIMD vector dot product (`simd_vector_dot8`), vector Euclidean norm (`simd_vector_norm8`), $4\times4$ matrix multiplication (`matrix_mul_4x4`), multi-asset covariance matrix estimation (`matrix_cov_from_returns`), Cholesky decomposition ($2\times2$ and $3\times3$), and $2\times2$ matrix inversion. |
| **Master Aggregator** | `src/dmc_quant.dmc` | Unified entry point importing all 12 quantitative libraries. |

---

## Quick Start & Installation

Install directly into any Demonic C project via the package manager:

```bash
dmc pkg add https://github.com/ak495867/dmc-quant.git
```

Import all capabilities in one line:

```dmc
import "dmc_quant";
```

---

## Interactive Quant Desk Simulation Demo

Run the end-to-end simulated trading desk demo:

```bash
dmc run examples/quant_desk_demo.dmc
```

Output:
```
================================================================================
                    DEMONIC C HIGH-FREQUENCY QUANT DESK DEMO                    
================================================================================
[1] Central Limit Order Book & Microstructure (AAPL):
    Best Bid:      $185.00 (qty: 700)
    Best Ask:      $185.20 (qty: 700)
    Spread:        $0.20 | Mid-Price: $185.10
    Order Imbalance (OBI): 0.000 | Micro-Price: $185.10

[2] Derivative Pricing & Greeks (AAPL 185C, 3M Expiry):
    Call Option:   $9.32
    Delta:         0.5689 | Gamma: 0.0193 | Vega: 36.3702

[3] Algorithmic Execution & FIX Protocol:
    Parent Order:  1000 shares -> Slice 1/5: 200 shares
    FIX 4.4 Msg:   8=FIX.4.4 9=77 35=D 49=QUANT_DESK 56=NASDAQ 11=TWAP_ORD_1 55=AAPL 54=1 38=200 44=185.2 40=2 10=012 
    Market Match:  Filled 200 shares @ $185.20 (Slippage: 0.00 bps)

[4] Decentralized Finance (AMM DEX vs CEX):
    DEX Reserve:   50,000 ETH / 9,250,000 USDC
    Swap 100 ETH:  Received 18407.79 USDC (Effective Px: $184.08)

[5] Fixed Income & Rates (US 10Y Treasury):
    Clean Price:   $102.43
    Mod Duration:  8.02 yrs | DV01: $0.0821

[6] Portfolio Engineering & Risk Management:
    Risk Parity:   Stock Weight: 26.7% | Bond Weight: 73.3%
    Portfolio VaR: $197382.36 (95% Daily, $1M Capital)
================================================================================
                         ALL DESK OPERATIONS EXECUTED OK                        
================================================================================
```

---

## ⚡ Benchmarks & Performance (`dmc bench benchmarks`)

```
Running 9 benchmark(s) from 9 file(s)...

PASS benchmarks\bench_amm.dmc                 (10,000 AMM constant product swaps in 0.001s)
PASS benchmarks\bench_fix.dmc                 (2,000 zero-allocation FIX messages in 0.000s)
PASS benchmarks\bench_fixed_income.dmc        (10,000 bond prices & durations in 0.004s)
PASS benchmarks\bench_lob.dmc                 (1,000 crossed limit orders in 0.007s)
PASS benchmarks\bench_matrix.dmc              (10,000 Cholesky factorizations in 0.000s)
PASS benchmarks\bench_microstructure.dmc       (10,000 VPIN & Order Imbalances in 0.000s)
PASS benchmarks\bench_pricing_analytical.dmc  (10,000 analytical option pricings in 0.001s ~ 10M options/sec)
PASS benchmarks\bench_pricing_simd.dmc        (80,000 options priced via 256-bit SIMD in 0.007s)
PASS benchmarks\bench_timeseries.dmc          (5,000 rolling SMA & RSI ticks in 0.001s)

Results: 9 passed, 0 failed
```

---

## 🧪 Testing

Run the test suite across all 13 test suites:

```bash
dmc test tests
```

Output:
```
Running 40 test(s) from 13 file(s)...

PASS tests\test_amm.dmc
PASS tests\test_execution.dmc
PASS tests\test_fix.dmc
PASS tests\test_fixed_income.dmc
PASS tests\test_lob.dmc
PASS tests\test_microstructure.dmc
PASS tests\test_ml_factors.dmc
PASS tests\test_portfolio.dmc
PASS tests\test_pricing.dmc
PASS tests\test_quant_all.dmc
PASS tests\test_risk.dmc
PASS tests\test_simd_matrix.dmc
PASS tests\test_timeseries.dmc

Results: 13 passed, 0 failed
```

---

## 🌐 Foreign Language Interop (C, C++, Python, Rust)

`dmc-quant` compiles to native shared libraries (`.dll`, `.so`, `.dylib`) with C ABI bindings:

```bash
dmc build src/dmc_quant.dmc --shared -o lib/dmc_quant.dll
```

Header definitions are located in [`include/dmc_quant.h`](include/dmc_quant.h) for direct inclusion in C/C++ or Python `ctypes` bindings.
