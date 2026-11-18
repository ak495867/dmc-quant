#ifndef DMC_QUANT_H
#define DMC_QUANT_H

#ifdef __cplusplus
extern "C" {
#endif

/* LOB Engine */
int lob_create(int book_id);
int lob_clear(int book_id);
int lob_add_limit(int book_id, int order_id, int side, int price, int qty);
int lob_add_market(int book_id, int side, int qty);
int lob_cancel(int book_id, int order_id);
int lob_best_bid(int book_id);
int lob_best_ask(int book_id);
int lob_spread(int book_id);
int lob_mid_price(int book_id);
int lob_depth_qty(int book_id, int side);
int lob_total_volume(int book_id);
int lob_last_price(int book_id);
int lob_level2_depth(int book_id, int side, int level, int* out_price, int* out_qty);

/* Derivative Pricing */
float bs_fast_cnd(float x);
float bs_call(float s, float k, float t, float r, float sigma);
float bs_put(float s, float k, float t, float r, float sigma);
float bs_delta_call(float s, float k, float t, float r, float sigma);
float bs_delta_put(float s, float k, float t, float r, float sigma);
float bs_gamma(float s, float k, float t, float r, float sigma);
float bs_vega(float s, float k, float t, float r, float sigma);
float bs_theta_call(float s, float k, float t, float r, float sigma);
float bs_rho_call(float s, float k, float t, float r, float sigma);
float bs_implied_vol(float s, float k, float t, float r, float market_price, int is_call);
float bs_monte_carlo(float s, float k, float t, float r, float sigma, int n_sims, int is_call);
float bs_monte_carlo_fast(float s, float k, float t, float r, float sigma, int n_sims, int is_call);
float crr_american_option(float s, float k, float t, float r, float sigma, int steps, int is_call);

/* Technical Time Series */
float ts_sma(float* prices, int count, int period);
float ts_ema(float* prices, int count, int period);
float ts_rsi(float* prices, int count, int period);
float ts_macd_line(float* prices, int count, int fast_p, int slow_p);
int ts_bollinger_bands(float* prices, int count, int period, float k, float* out_upper, float* out_mid, float* out_lower);
float ts_volatility(float* returns, int count);
float ts_skewness(float* returns, int count);
float ts_kurtosis(float* returns, int count);
float ts_covariance(float* x, float* y, int count);
float ts_correlation(float* x, float* y, int count);
float ts_simd_dot(float* a, float* b, int count);
float ts_simd_sum(float* arr, int count);
float ts_ewma_volatility(float* returns, int count, float lambda_decay);
float ts_autocorrelation(float* series, int count, int lag);
float ts_rolling_zscore(float* prices, int count, int period);

/* Fixed Income */
float fi_bond_price(float face_value, float coupon_rate, float ytm, float years, int freq);
float fi_bond_ytm(float face_value, float coupon_rate, float market_price, float years, int freq);
float fi_macaulay_duration(float face_value, float coupon_rate, float ytm, float years, int freq);
float fi_modified_duration(float face_value, float coupon_rate, float ytm, float years, int freq);
float fi_bond_convexity(float face_value, float coupon_rate, float ytm, float years, int freq);
float fi_dv01(float face_value, float coupon_rate, float ytm, float years, int freq);
float fi_discount_factor(float zero_rate, float maturity);
float fi_forward_rate(float spot1, float t1, float spot2, float t2);

/* Market Microstructure */
float micro_order_book_imbalance(int bid_qty, int ask_qty);
float micro_price(float bid_price, float ask_price, int bid_qty, int ask_qty);
float micro_vpin(float* buy_volume_buckets, float* sell_volume_buckets, int num_buckets, float bucket_size);
float micro_kyles_lambda(float* price_changes, float* signed_order_flows, int count);
float micro_amihud_illiquidity(float* returns, float* volumes_dollar, int count);
float micro_roll_spread(float* price_changes, int count);
float micro_realized_spread(float trade_price, float mid_t, float mid_future, int side);

/* Decentralized Finance & AMM */
float amm_spot_price(float reserve_in, float reserve_out);
float amm_get_amount_out(float amount_in, float reserve_in, float reserve_out, int fee_bps);
float amm_get_amount_in(float amount_out, float reserve_in, float reserve_out, int fee_bps);
float amm_slippage_bps(float amount_in, float reserve_in, float reserve_out, int fee_bps);
float amm_impermanent_loss(float price_ratio);
float amm_optimal_arbitrage_input(float r1_in, float r1_out, float r2_in, float r2_out, int fee_bps);
float amm_tick_to_price(int tick);

/* Portfolio Optimization */
int port_normalize_weights(float* w, int count);
int port_min_variance_2asset(float vol1, float vol2, float corr, float* out_w1, float* out_w2);
int port_tangency_2asset(float r1, float r2, float vol1, float vol2, float corr, float rf, float* out_w1, float* out_w2);
int port_risk_parity_weights(float* vols, int count, float* out_weights);
float port_calc_return(float* weights, float* returns, int count);
float port_calc_variance(float* weights, float* cov_flat, int count);
int port_rebalance_shares(int* curr_shares, float* prices, float* target_weights, float total_capital, int count, int* out_trade_shares);
float port_cagr(float start_val, float end_val, float years);

/* Algorithmic Execution */
int exec_twap_slice(int total_qty, int num_slices, int slice_idx);
int exec_vwap_slice(int total_qty, int bucket_volume, int total_projected_volume);
int exec_pov_slice(int market_volume, float target_participation_rate);
float exec_implementation_shortfall(float decision_price, float avg_execution_price, int total_qty, int side);
float exec_slippage_bps(float decision_price, float avg_execution_price, int side);

/* Alpha Factor Modeling */
int factor_zscore(float* vals, int count, float* out_zscores);
int factor_winsorize(float* vals, int count, float lower_pct, float upper_pct, float* out_vals);
float factor_ornstein_uhlenbeck_halflife(float* series, int count);
float factor_information_coefficient(float* signals, float* fwd_returns, int count);
int factor_rank(float* vals, int count, float* out_ranks);
float factor_spearman_ic(float* signals, float* fwd_returns, int count);

/* Risk Engine */
float risk_parametric_var(float portfolio_value, float vol, float confidence);
float risk_historical_var(float* returns, int count, float confidence);
float risk_cvar(float* returns, int count, float confidence);
float risk_sharpe_ratio(float mean_return, float risk_free_rate, float vol);
float risk_sortino_ratio(float* returns, int count, float target_return);
float risk_max_drawdown(float* equity_curve, int count);
float risk_calmar_ratio(float cagr, float max_drawdown);
float risk_beta(float* asset_returns, float* market_returns, int count);
float risk_omega_ratio(float* returns, int count, float threshold);
float risk_tail_ratio(float* returns, int count, float percentile);

/* SIMD Linear Algebra */
int matrix_cholesky_2x2(float a00, float a01, float a11, float* out_l00, float* out_l10, float* out_l11);
int matrix_cholesky_3x3(float* cov, float* out_l);
int matrix_invert_2x2(float a00, float a01, float a10, float a11, float* out_inv);
int matrix_vector_mul_3x3(float* mat, float* vec, float* out_res);
int matrix_mul_4x4(float* a, float* b, float* out_c);
int matrix_cov_from_returns(float* returns_flat, int num_assets, int num_periods, float* out_cov);

#ifdef __cplusplus
}
#endif

#endif
