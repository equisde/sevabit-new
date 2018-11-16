// Copyright (c) 2014-2018, The Monero Project
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#include "chaingen.h"
#include "service_nodes.h"

using namespace std;

using namespace epee;
using namespace cryptonote;

static const std::pair<const char*, const char*> service_node_keys[] = {
  { "1c09e237e7f451ee5df4ea6db970ba0b17597d788106df0c3b436a8ff8c94806",
    "06d471cbb6d67cae5002f18dd1c46ae6307b474b6fad4d720bd639513438f219" },
  { "8336af81ddffa292122064b8ffa26977b76efdcfa441604b6013f43dd8e90101",
    "fe979e53de1f82458f000d84bb8bfb6013153a7811a19a5b4d534794cb87c311" },
  { "b0169fced37d767a33a975ae3f8f7a12c3034e654024c62ce5de2a6e163b5b05",
    "beca119a8a5581d0209a155f974e5331f08df48dbb3e11399f87867aae1973cc" },
  { "ee451af460163d7940a79f48890509ebc3efb5aad014c21964707dea8c604d0f",
    "7897152e723644d325eb10e677197cfebd630c4e6be6908330ec1f47094e8b35" },
  { "d0704bb98564800a5554c400da220b0265b338c37b80a5cd8af4b010b57cb301",
    "50483a668bf25d989a25d87f233835df3357c7e72000762529984d8c111a2c52" },
  { "878b8c4560499fdb929ebd5d9bd124603bcc7f3495c9581edcbdf7360fa51706",
    "467ba9a442a9d2dfa8e4f9f07dd49e40554b299a9144f3fef392e8c5e1038cd7" },
  { "9dae6882b90ddc63b1832500fcccd7d027ea1081db9127f27316d16708b96c0a",
    "151c6ccbfd05465d2752d6794dc2892381a284750597b8b321b712036cda3c4a" },
  { "91bab98d4c9bfbe39c84effb68cb7a68020f16583f0eca0e60c1cae1cf13920e",
    "b16768d1a95d653310941c75e9ab9dcb6c79019195def04fd2279f67e32a4b7b" },
  { "a0a5daa0ddd972551147c48a223800c27a38eb156ff97d9c0e7595089bc04203",
    "090788a7faeab266a3fe1d755df1e58a989e676ea5d94a2c748b5b94ad30ee30" },
  { "992f5da1cd19727a03becaacd21251485ddf4ffaa827b44d6c5ff9a2ec1d5402",
    "f20624bc19ec1486ad49c0994faf4523b471fa53bf0bf856d142cdaf13b93165" },
  { "1a87c618ff444e324a0212e26e14af65670d566363b204300102afcaa085590c",
    "f3bd64b0ba024ad8068b2e96213e6b7d354d13f468a2775e2fd22a85f352aa73" },
  { "8b079185e6e1df1b61d18a7b71fdea149e6555271fae055c28e3fe7174abc107",
    "3b4d8725de3a16615358dad594114224a9fff21d5c6f4680528840b17e19e02b" },
  { "a01f14e058a0c414577e978f3e290cf662ae670fdee6699c57b14c9c4a452706",
    "ff099e244736503eb32b6a869674c9bb1f2a29590026f2680968cbae9c466a41" },
  { "3c9d7ecac68bb506c0eb4b1de21839f14afd59ae292b55ce7c104322eca4e308",
    "2a1d51e4f6f36ab79f1c642a9ab109eb34527fd1e4e9f130127662ca3c8a0fb9" },
  { "af7e04cf1f0816c66ee0b72fcad40e577bbffd10a391245c2b5b29c87a7a1304",
    "0a25fae0eeb6418a291d0e93410510f2cb66b1cfa897398c9196737fbe19f35d" },
  { "b861b35dc2479652c37d5afcc4231b6363172ee73e4bf88b52a1a33e52490f0f",
    "03cc9506ecf7acd5b13bbb5d3b59e4d4e3ff408f70622b9db131d0c120b841d0" },
  { "834b35e68c7fc5bcf56ed772bb5d72e08dcc38b987f16e52d79e9df2f9b7ec00",
    "5f40d0c72036a85163ea97a23ef67b8c52c06f5eee59bfb03db1ff07b761604c" },
  { "441e071ba14153d0a931f9eaa7ee4dbae4306d2921865f2f3a7cc625b4fbc60b",
    "836bbceec1b80f82e2edb43e3583cbc3a09925e16c5c66a08b94899de5fb59ce" },
  { "9c6e82db18c537c333b28b515cb25708ed42e22f3c9948511890389ea79e3d08",
    "2d848c307f1e734af4dd1f09cc132038d6e0a5fc8223e4548094a3e354f43aec" },
  { "3f4472d29b95c742ad092ca603f2b888f7a699b000d9fdb7ca003ee86218cf02",
    "356cf984c6a9efd2ca965bfdbb2d94d2906113e1a7acabf5dbda6a4911bd43fc" },
  { "78b784f007f7d1f80c6b6da2627b4f47c37f88ac96c7a0006e02727cd2b7770b",
    "b1f24cf86553b1fc72ed5a9a09286200cdf62dabc52683ba61ee95b6d9b64679" },
  { "c8489fe5119e2ea00116a33ac38ec0636312dadeffe3a85967ae5243afd3a005",
    "9d6bbe3c47d0994bd3383e88e84f1ab4daac4fd28843490ce5d101f1b52d4875" },
  { "7b9a1077d3ba10833b596d4c254ae2dc26c8b801807a3c61f78e8055aba19a04",
    "b88af38e69c4fd44d95c3f41b551d9c41edb834331be2e85a3693f7a3eaa2004" },
  { "8376b213f06785788bde97027caab42384f2249d272c4eefc15ef9cc02efa302",
    "5e2033fe1a5d4bf21952934b2a4b005d57075861baafc26d98c7e090d8ecbcac" },
  { "fad6778760c4f357559131f77ea3f2fb7e92cfb660bad72c0a37b29f8e37030c",
    "30660777ff79db10e735be0c79732d0cbd15d5812a59e3467fb6b4a7bc71a601" }
};

static const auto SN_KEYS_COUNT = sizeof(service_node_keys) / sizeof(service_node_keys[0]);

cryptonote::keypair get_static_keys(size_t idx) {

  if (idx >= SN_KEYS_COUNT) { MERROR("out of bounds"); throw std::exception(); }

  cryptonote::keypair keypair;

  epee::string_tools::hex_to_pod(service_node_keys[idx].first, keypair.sec);
  epee::string_tools::hex_to_pod(service_node_keys[idx].second, keypair.pub);

  return keypair;
}

struct last_reward_point {
  uint64_t height;
  uint64_t priority;
};

bool operator<(const last_reward_point& lhs, const last_reward_point& rhs) {
  if (lhs.height != rhs.height) {
    return lhs.height < rhs.height;
  }

  return lhs.priority < rhs.priority;
}

struct sn_registration {
  uint64_t valid_until; /// block height
  cryptonote::keypair keys;
  sn_contributor_t contribution;
  last_reward_point last_reward;
};

/// Service node and its index
struct sn_idx {
  crypto::public_key sn_pk;
  /// index in the sorted list of service nodes for a particular block
  size_t idx_in_quorum;
};

struct QuorumState {
  std::vector<sn_idx> voters;
  std::vector<sn_idx> to_test;
};

class sn_list
{
  std::vector<sn_registration> sn_owners_;

public:

  const sn_registration& at(size_t idx) const { return sn_owners_.at(idx); }

  const boost::optional<sn_registration> find_registration(const crypto::public_key& pk) const;

  void expire_old(uint64_t height);

  const boost::optional<crypto::public_key> get_winner_pk(uint64_t height);

  size_t size() const { return sn_owners_.size(); }

  void add_registrations(const std::vector<sn_registration>& regs);

  void remove_node(const crypto::public_key& pk);
};

inline void sn_list::remove_node(const crypto::public_key& pk)
{
  const auto it =
    std::find_if(sn_owners_.begin(), sn_owners_.end(), [pk](const sn_registration& sn) { return sn.keys.pub == pk; });
  if (it != sn_owners_.end()) sn_owners_.erase(it); else abort();
}

inline void sn_list::add_registrations(const std::vector<sn_registration>& regs)
{
  sn_owners_.insert(sn_owners_.begin(), regs.begin(), regs.end());

  std::sort(sn_owners_.begin(), sn_owners_.end(),
  [](const sn_registration &a, const sn_registration &b) {
    return memcmp(reinterpret_cast<const void*>(&a.keys.pub), reinterpret_cast<const void*>(&b.keys.pub),
    sizeof(a.keys.pub)) < 0;
  });
}

inline void sn_list::expire_old(uint64_t height)
{
  /// remove_if is stable, no need for re-sorting
  const auto new_end = std::remove_if(
    sn_owners_.begin(), sn_owners_.end(), [height](const sn_registration& reg) { return reg.valid_until < height; });

  sn_owners_.erase(new_end, sn_owners_.end());
}

inline const boost::optional<sn_registration> sn_list::find_registration(const crypto::public_key& pk) const
{
  const auto it =
    std::find_if(sn_owners_.begin(), sn_owners_.end(), [pk](const sn_registration& sn) { return sn.keys.pub == pk; });

  if (it == sn_owners_.end()) return boost::none;

  return *it;
}

inline const boost::optional<crypto::public_key> sn_list::get_winner_pk(uint64_t height)
{
  if (sn_owners_.empty()) return boost::none;

  auto it =
    std::min_element(sn_owners_.begin(), sn_owners_.end(), [](const sn_registration& lhs, const sn_registration& rhs) {
      return lhs.last_reward < rhs.last_reward;
    });

  it->last_reward.height = height;

  return it->keys.pub;
}

class dereg_tx_builder;

class linear_chain_generator
{

  private:
    test_generator gen_;
    std::vector<test_event_entry>& events_;
    std::vector<cryptonote::block> blocks_;

    sn_list sn_list_;

    /// keep new registrations here until the next block
    std::vector<sn_registration> registration_buffer_;

    cryptonote::account_base first_miner_;

  public:
    linear_chain_generator(std::vector<test_event_entry> &events)
      : gen_(), events_(events)
    { }

    uint64_t height() const { return get_block_height(blocks_.back()); }

    cryptonote::account_base create_account();

    void create_genesis_block();

    void create_block(const std::vector<cryptonote::transaction>& txs = {});

    cryptonote::block create_block_on_fork(const cryptonote::block& prev, const std::vector<cryptonote::transaction>& txs = {});

    void rewind_until_v9();
    void rewind_blocks_n(int n);
    void rewind_blocks();

    cryptonote::transaction create_tx(const cryptonote::account_base& miner,
                                      const cryptonote::account_base& acc,
                                      uint64_t amount,
                                      uint64_t fee = TESTS_DEFAULT_FEE);

    cryptonote::transaction create_registration_tx(const cryptonote::account_base& acc, const cryptonote::keypair& sn_keys);

    cryptonote::transaction create_registration_tx();

    const cryptonote::account_base& first_miner() const { return first_miner_; }

    /// Note: should be carefull with returing a reference to vector elements
    const cryptonote::block& chain_head() const { return blocks_.back(); }

    /// get a copy of the service node list
    sn_list get_sn_list() const { return sn_list_; }

    void set_sn_list(const sn_list& list) { sn_list_ = list; }

    QuorumState get_quorum_idxs(uint64_t height) const;

    cryptonote::transaction create_deregister_tx(const crypto::public_key& pk, uint64_t height, const std::vector<sn_idx>& voters, uint64_t fee = 0) const;

    dereg_tx_builder build_deregister(const crypto::public_key& pk);

    crypto::public_key get_test_pk(uint32_t idx) const;

    boost::optional<uint32_t> get_idx_in_tested(const crypto::public_key& pk, uint64_t height) const;

    void deregister(const crypto::public_key& pk) {
      sn_list_.remove_node(pk);
    }

};

class dereg_tx_builder {

  linear_chain_generator& gen_;
  const crypto::public_key& pk_;

  /// the height at which `pk_` is to be found
  boost::optional<uint64_t> height_ = boost::none;

  boost::optional<uint64_t> fee_ = boost::none;

  boost::optional<const std::vector<sn_idx>&> voters_ = boost::none;

  public:
    dereg_tx_builder(linear_chain_generator& gen, const crypto::public_key& pk)
      : gen_(gen), pk_(pk)
    {}

    dereg_tx_builder&& with_height(uint64_t height) {
      height_ = height;
      return std::move(*this);
    }

    dereg_tx_builder&& with_fee(uint64_t fee) {
      fee_ = fee;
      return std::move(*this);
    }

    dereg_tx_builder&& with_voters(const std::vector<sn_idx>& voters)
    {
      voters_ = voters;
      return std::move(*this);
    }

    cryptonote::transaction build()
    {
      const auto height = height_ ? *height_ : gen_.height();
      const auto voters = voters_ ? *voters_ : gen_.get_quorum_idxs(height).voters;
      return gen_.create_deregister_tx(pk_, height, voters, fee_.value_or(0));
    }

};

dereg_tx_builder linear_chain_generator::build_deregister(const crypto::public_key& pk)
{
  return dereg_tx_builder(*this, pk);
}

cryptonote::account_base linear_chain_generator::create_account()
{
  cryptonote::account_base account;
  account.generate();
  events_.push_back(account);
  return account;
}

void linear_chain_generator::create_genesis_block()
{
  constexpr uint64_t ts_start = 1338224400;
  first_miner_.generate();
  cryptonote::block gen_block;
  gen_.construct_block(gen_block, first_miner_, ts_start);
  events_.push_back(gen_block);
  blocks_.push_back(gen_block);
}

void linear_chain_generator::create_block(const std::vector<cryptonote::transaction>& txs)
{
  const auto blk = create_block_on_fork(blocks_.back(), txs);
  blocks_.push_back(blk);
}

void linear_chain_generator::rewind_until_v9()
{
  gen_.set_hf_version(8);
  create_block();
  gen_.set_hf_version(9);
  create_block();
}

void linear_chain_generator::rewind_blocks_n(int n)
{
  for (auto i = 0; i < n; ++i) {
    create_block();
  }
}

void linear_chain_generator::rewind_blocks()
{
  rewind_blocks_n(CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW);
}

cryptonote::block linear_chain_generator::create_block_on_fork(const cryptonote::block& prev,
                                                               const std::vector<cryptonote::transaction>& txs)
{

  const auto height = get_block_height(prev) + 1;

  const auto& winner_pk = sn_list_.get_winner_pk(height);

  const auto& sn_pk = winner_pk ? *winner_pk : crypto::null_pkey;

  std::vector<sn_contributor_t> contribs = { { { crypto::null_pkey, crypto::null_pkey }, STAKING_PORTIONS } };

  if (winner_pk) {
    const auto& reg = sn_list_.find_registration(*winner_pk);
    if (reg) {
      contribs = { reg->contribution };
    }
  }

  cryptonote::block blk;
  gen_.construct_block(blk, prev, first_miner_, { txs.begin(), txs.end() }, sn_pk, contribs);
  events_.push_back(blk);

  /// now we can add sn from the buffer to be used in consequent nodes
  sn_list_.add_registrations(registration_buffer_);
  registration_buffer_.clear();
  sn_list_.expire_old(height);

  return blk;
}

QuorumState linear_chain_generator::get_quorum_idxs(uint64_t height) const
{
  const auto block = blocks_.at(height);

  if (sn_list_.size() <= service_nodes::QUORUM_SIZE) {
    std::cerr << "Not enough service nodes\n";
    return {};
  }

  std::vector<size_t> pub_keys_indexes;
  {
    uint64_t seed = 0;
    const crypto::hash block_hash = cryptonote::get_block_hash(block);
    std::memcpy(&seed, block_hash.data, std::min(sizeof(seed), sizeof(block_hash.data)));

    pub_keys_indexes.resize(sn_list_.size());
    for (size_t i = 0; i < pub_keys_indexes.size(); i++) {
      pub_keys_indexes[i] = i;
    }

    service_nodes::sevabit_shuffle(pub_keys_indexes, seed);
  }

  QuorumState quorum;

  for (auto i = 0u; i < service_nodes::QUORUM_SIZE; ++i) {
    quorum.voters.push_back({ sn_list_.at(pub_keys_indexes[i]).keys.pub, i });
  }

  for (auto i = service_nodes::QUORUM_SIZE; i < pub_keys_indexes.size(); ++i) {
    quorum.to_test.push_back({ sn_list_.at(pub_keys_indexes[i]).keys.pub, i });
  }

  return quorum;
}

cryptonote::transaction linear_chain_generator::create_tx(const cryptonote::account_base& miner,
                                                          const cryptonote::account_base& acc,
                                                          uint64_t amount,
                                                          uint64_t fee)
{
  cryptonote::transaction t;
  construct_tx_to_key(events_, t, blocks_.back(), miner, acc, amount, fee, 9);
  events_.push_back(t);
  return t;
}

cryptonote::transaction linear_chain_generator::create_registration_tx(const cryptonote::account_base& acc,
                                                                       const cryptonote::keypair& sn_keys)
{
  const sn_contributor_t contr = { acc.get_keys().m_account_address, STAKING_PORTIONS };
  const uint32_t expires = height() + service_nodes::get_staking_requirement_lock_blocks(cryptonote::FAKECHAIN);

  const auto reg_idx = registration_buffer_.size();
  registration_buffer_.push_back({ expires, sn_keys, contr, { height(), reg_idx } });
  return make_default_registration_tx(events_, acc, sn_keys, blocks_.back());
}

cryptonote::transaction linear_chain_generator::create_registration_tx()
{
  const auto sn_keys = keypair::generate(hw::get_device("default"));

  return create_registration_tx(first_miner_, sn_keys);
}

cryptonote::transaction linear_chain_generator::create_deregister_tx(const crypto::public_key& pk,
                                                                     uint64_t height,
                                                                     const std::vector<sn_idx>& voters,
                                                                     uint64_t fee) const
{

  cryptonote::tx_extra_service_node_deregister deregister;
  deregister.block_height = height;

  const auto idx = get_idx_in_tested(pk, height);

  if (!idx) { MERROR("service node could not be found in the servcie node list"); throw std::exception(); }

  deregister.service_node_index = *idx; /// idx inside nodes to test

  /// need to create MIN_VOTES_TO_KICK_SERVICE_NODE (7) votes
  for (const auto voter : voters) {

    const auto reg = sn_list_.find_registration(voter.sn_pk);

    if (!reg) return {};

    const auto pk = reg->keys.pub;
    const auto sk = reg->keys.sec;
    const auto signature =
      sevabit::service_node_deregister::sign_vote(deregister.block_height, deregister.service_node_index, pk, sk);

    deregister.votes.push_back({ signature, (uint32_t)voter.idx_in_quorum });
  }

  const auto deregister_tx = make_deregistration_tx(events_, first_miner_, blocks_.back(), deregister, fee);

  events_.push_back(deregister_tx);

  return deregister_tx;
}

crypto::public_key linear_chain_generator::get_test_pk(uint32_t idx) const
{
  const auto& to_test = get_quorum_idxs(height()).to_test;

  return to_test.at(idx).sn_pk;
}

boost::optional<uint32_t> linear_chain_generator::get_idx_in_tested(const crypto::public_key& pk, uint64_t height) const
{
  const auto& to_test = get_quorum_idxs(height).to_test;

  for (const auto& sn : to_test) {
    if (sn.sn_pk == pk) return sn.idx_in_quorum - service_nodes::QUORUM_SIZE;
  }

  return boost::none;
}

//-----------------------------------------------------------------------------------------------------
//---------------------------------- Generate Service Nodes -------------------------------------------
//-----------------------------------------------------------------------------------------------------
gen_service_nodes::gen_service_nodes()
{
  /// NOTE: we don't generate random keys here, because the verification will call its own constructor
  m_alice_service_node_keys = get_static_keys(0);

  REGISTER_CALLBACK("check_registered", gen_service_nodes::check_registered);
  REGISTER_CALLBACK("check_expired", gen_service_nodes::check_expired);
}
//-----------------------------------------------------------------------------------------------------
bool gen_service_nodes::generate(std::vector<test_event_entry> &events) const
{

  linear_chain_generator gen(events);
  gen.create_genesis_block();                           //  1

  const auto miner = gen.first_miner();
  const auto alice = gen.create_account();

  gen.rewind_until_v9();                                //  3
  gen.rewind_blocks_n(10);                              // 13

  gen.rewind_blocks();                                  // 13 + N

  const auto tx0 = gen.create_tx(miner, alice, MK_COINS(101));
  gen.create_block({tx0});                              // 14 + N

  gen.rewind_blocks();                                  // 14 + 2N

  const auto reg_tx = gen.create_registration_tx(alice, m_alice_service_node_keys);

  gen.create_block({reg_tx});                           // 15 + 2N

  DO_CALLBACK(events, "check_registered");

  for (auto i = 0u; i < service_nodes::get_staking_requirement_lock_blocks(cryptonote::FAKECHAIN); ++i) {
    gen.create_block();
  } // 15 + 2N + M

  DO_CALLBACK(events, "check_expired");

  return true;
}
//-----------------------------------------------------------------------------------------------------
bool gen_service_nodes::check_registered(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events)
{
  DEFINE_TESTS_ERROR_CONTEXT("gen_service_nodes::check_registered");

  cryptonote::account_base alice = boost::get<cryptonote::account_base>(events[1]);

  std::vector<block> block_list;
  bool r = c.get_blocks(0, 15 + 2 * CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW, block_list);
  CHECK_TEST_CONDITION(r);
  std::vector<cryptonote::block> chain;
  map_hash2tx_t mtx;
  std::vector<block> blocks(block_list.begin(), block_list.end());
  r = find_block_chain(events, chain, mtx, get_block_hash(blocks.back()));
  CHECK_TEST_CONDITION(r);

  const uint64_t staking_requirement = MK_COINS(100);

  CHECK_EQ(MK_COINS(101) - TESTS_DEFAULT_FEE - staking_requirement, get_unlocked_balance(alice, blocks, mtx));

  /// check that alice is registered
  const auto info_v = c.get_service_node_list_state({m_alice_service_node_keys.pub});
  CHECK_EQ(info_v.empty(), false);

  return true;
}
//-----------------------------------------------------------------------------------------------------
bool gen_service_nodes::check_expired(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events)
{
  DEFINE_TESTS_ERROR_CONTEXT("gen_service_nodes::check_expired");

  cryptonote::account_base alice = boost::get<cryptonote::account_base>(events[1]);

  const auto stake_lock_time = service_nodes::get_staking_requirement_lock_blocks(cryptonote::FAKECHAIN);

  std::vector<block> block_list;

  bool r = c.get_blocks(0, 15 + 2 * CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW + stake_lock_time, block_list);
  CHECK_TEST_CONDITION(r);
  std::vector<cryptonote::block> chain;
  map_hash2tx_t mtx;
  std::vector<block> blocks(block_list.begin(), block_list.end());
  r = find_block_chain(events, chain, mtx, get_block_hash(blocks.back()));
  CHECK_TEST_CONDITION(r);

  /// check that alice's registration expired
  const auto info_v = c.get_service_node_list_state({m_alice_service_node_keys.pub});
  CHECK_EQ(info_v.empty(), true);

  /// check that alice received some service node rewards (TODO: check the balance precisely)
  CHECK_TEST_CONDITION(get_balance(alice, blocks, mtx) > MK_COINS(101) - TESTS_DEFAULT_FEE);

  return true;

}
//-----------------------------------------------------------------------------------------------------
//------------------------------ Test Blocks Prefer Deregisters ---------------------------------------
//-----------------------------------------------------------------------------------------------------
test_prefer_deregisters::test_prefer_deregisters() {
  REGISTER_CALLBACK("check_prefer_deregisters", test_prefer_deregisters::check_prefer_deregisters);
}
//-----------------------------------------------------------------------------------------------------
bool test_prefer_deregisters::generate(std::vector<test_event_entry> &events)
{
  linear_chain_generator gen(events);

  gen.create_genesis_block();

  const auto miner = gen.first_miner();
  const auto alice = gen.create_account();

  gen.rewind_until_v9();

  /// give miner some outputs to spend and unlock them
  gen.rewind_blocks_n(60);
  gen.rewind_blocks();

  /// register 12 random service nodes
  std::vector<cryptonote::transaction> reg_txs;
  for (auto i = 0; i < 12; ++i) {
    const auto tx = gen.create_registration_tx();
    reg_txs.push_back(tx);
  }

  gen.create_block(reg_txs);

  /// generate transactions to fill up txpool entirely
  for (auto i = 0u; i < 45; ++i) {
    gen.create_tx(miner, alice, MK_COINS(1), TESTS_DEFAULT_FEE * 100);
  }

  /// generate two deregisters
  const auto pk1 = gen.get_test_pk(0);
  const auto pk2 = gen.get_test_pk(1);

  gen.build_deregister(pk1).build();
  gen.build_deregister(pk2).build();

  DO_CALLBACK(events, "check_prefer_deregisters");

  return true;
}
//-----------------------------------------------------------------------------------------------------
bool test_prefer_deregisters::check_prefer_deregisters(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events)
{

  DEFINE_TESTS_ERROR_CONTEXT("test_prefer_deregisters::check_prefer_deregisters");

  const auto tx_count = c.get_pool_transactions_count();

  cryptonote::block full_blk;
  {
    difficulty_type diffic;
    uint64_t height;
    uint64_t expected_reward;
    cryptonote::blobdata extra_nonce;
    const auto miner = boost::get<cryptonote::account_base>(events[1]);
    c.get_block_template(full_blk, miner.get_keys().m_account_address, diffic, height, expected_reward, extra_nonce);
  }

  map_hash2tx_t mtx;
  {
    std::vector<cryptonote::block> chain;
    CHECK_TEST_CONDITION(find_block_chain(events, chain, mtx, get_block_hash(boost::get<cryptonote::block>(events[0]))));
  }

  const auto deregister_count =
    std::count_if(full_blk.tx_hashes.begin(), full_blk.tx_hashes.end(), [&mtx](const crypto::hash& tx_hash) {
      return mtx[tx_hash]->is_deregister;
    });

  /// test that there are more transactions in tx pool
  CHECK_TEST_CONDITION(tx_count > full_blk.tx_hashes.size());
  /// test that all 2 deregister tx are in the block
  CHECK_EQ(deregister_count, 2);

  return true;

}
//-----------------------------------------------------------------------------------------------------
//------------------------------ Test Zero-Fee Deregisters Fail ---------------------------------------
//-----------------------------------------------------------------------------------------------------
test_zero_fee_deregister::test_zero_fee_deregister() {
  // Test that deregister that are non-zero fee don't get accepted onto the blockchain or anywhere.
  REGISTER_CALLBACK_METHOD(test_zero_fee_deregister, mark_invalid_tx);
}
//-----------------------------------------------------------------------------------------------------
bool test_zero_fee_deregister::generate(std::vector<test_event_entry> &events)
{

  linear_chain_generator gen(events);

  gen.create_genesis_block();

  gen.rewind_until_v9();

  /// give miner some outputs to spend and unlock them
  gen.rewind_blocks_n(20);
  gen.rewind_blocks();

  /// register 11 random service nodes
  std::vector<cryptonote::transaction> reg_txs;
  for (auto i = 0; i < 11; ++i) {
    const auto tx = gen.create_registration_tx();
    reg_txs.push_back(tx);
  }

  gen.create_block(reg_txs);
  /// create a deregister with a fee, should fail
  DO_CALLBACK(events, "mark_invalid_tx");
  const auto pk = gen.get_test_pk(0);
  gen.build_deregister(pk).with_fee(MK_COINS(1)).build();

  return true;
}
//-----------------------------------------------------------------------------------------------------
//-------------------------------- Test Deregister Safety Buffer --------------------------------------
//-----------------------------------------------------------------------------------------------------

// Test if a person registers onto the network and they get included in the nodes to test (i.e. heights 0, 5, 10). If
// they get dereigstered in the nodes to test, height 5, and rejoin the network before height 10 (and are in the nodes
// to test), they don't get deregistered. This scenario will most likely happen with an autostaker.
test_deregister_safety_buffer::test_deregister_safety_buffer() {
  REGISTER_CALLBACK_METHOD(test_deregister_safety_buffer, mark_invalid_tx);
}
//-----------------------------------------------------------------------------------------------------
bool test_deregister_safety_buffer::generate(std::vector<test_event_entry> &events)
{
  DEFINE_TESTS_ERROR_CONTEXT("test_deregister_safety_buffer::generate");

  linear_chain_generator gen(events);

  gen.create_genesis_block();

  const auto miner = gen.first_miner();

  gen.rewind_until_v9();

  /// give miner some outputs to spend and unlock them
  gen.rewind_blocks_n(40);
  gen.rewind_blocks();

  /// save generated keys here
  std::vector<cryptonote::keypair> used_sn_keys;

  /// register 21 random service nodes
  std::vector<cryptonote::transaction> reg_txs;

  constexpr auto SERVICE_NODES_NEEDED = service_nodes::QUORUM_SIZE * 2 + 1;
  static_assert(SN_KEYS_COUNT >= SERVICE_NODES_NEEDED, "not enough pre-computed service node keys");

  for (auto i = 0u; i < SERVICE_NODES_NEEDED; ++i)
  {
    const auto sn_keys = get_static_keys(i);
    used_sn_keys.push_back(sn_keys);

    const auto tx = gen.create_registration_tx(miner, sn_keys);
    reg_txs.push_back(tx);
  }

  gen.create_block({reg_txs});

  const auto heightA = gen.height();

  /// Note: would've used sets, but need `less` for public keys etc.
  std::vector<crypto::public_key> sn_set_A;

  for (const auto& sn : gen.get_quorum_idxs(heightA).to_test) {
    sn_set_A.push_back(sn.sn_pk);
  }

  /// create 5 blocks and find public key to be tested twice
  for (auto i = 0; i < 5; ++i) {
    gen.create_block();
  }

  const auto heightB = gen.height();

  std::vector<crypto::public_key> sn_set_B;

  for (const auto& sn : gen.get_quorum_idxs(heightB).to_test) {
    sn_set_B.push_back(sn.sn_pk);
  }

  /// Guaranteed to contain at least one element
  std::vector<crypto::public_key> tested_twice;

  for (const auto& sn : sn_set_A) {
    if (std::find(sn_set_B.begin(), sn_set_B.end(), sn) != sn_set_B.end()) {
      tested_twice.push_back(sn);
    }
  }

  /// Pick a node to deregister
  const auto pk = tested_twice.at(0);

  /// Deregister for heightA
  {
    const auto dereg_tx = gen.build_deregister(pk).with_height(heightA).build();
    gen.create_block({dereg_tx});
  }

  /// Register the node again
  {
    // find secret key for pk:
    auto it = std::find_if(used_sn_keys.begin(), used_sn_keys.end(), [&pk](const cryptonote::keypair& keys) {
      return keys.pub == pk;
    });

    if (it == used_sn_keys.end()) { MERROR("SN pub key not found in generated keys"); return false; };

    const auto tx = gen.create_registration_tx(miner, *it);
    gen.create_block({tx});
  }

  /// Try to deregister the node again for heightB (should fail)
  {
    DO_CALLBACK(events, "mark_invalid_tx");
    const auto dereg_tx = gen.build_deregister(pk).with_height(heightB).build();
  }

  return true;

}