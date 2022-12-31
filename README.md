# Bitcoin-Miner-Simulator:

Skills Data Structures | Multi Threading | Concurrency | Mutex Locks | Computation

BitCoin is a virtual currency that is managed by peer-to-peer network of computers instead of banks.   To make a bitcoin transaction a digitally signed message is broadcast in the peer-to-peer network.  Each transaction includes the

• ID: a unique identifier

• payer: the source of the funds (the transaction is digitally signed by the payer)

• payee: the receiver of the funds

• amount: the amount of the funds

• fee: the amount of bitcoin that will be paid for processing the transaction (by the payer)

• signature: of the payer to authenticate the transaction

• Other information

Transactions are processed by adding them to a digital ledger called a blockchain.  A blockchain is simply a sequence of blocks where each block stores a series of transactions and has a reference and the signa- ture of the previous block in the chain.  Consequently, it makes it computationally infeasible to modify (forge) a block because all blocks succeeding it would also need to be modified.  Thus, if Transaction 7 in Block 1 was to be modified, Block 1’s signature would change, requiring Block 2 to be updated, requiring Block 3 to be updated, and so on. This is computationally infeasible because to generate a block (mining) requires a lot of computation.



Mining

One way to become rich is to mine blocks. The payment for mining a block is one bitcoin.  As transactions are broadcast in the peer-to-peer network, they are aggregated by hosts in the network called miners. An aggregate of transactions that have not yet been added to a block is called a mempool (short for memory pool). To mine a block, a miner selects a set of transactions from the mempool and computes a new block. To compute a block the miner assembles the transactions in memory, along with the block’s number, the previous block’s number, the previous block’s signature, and a nonce.  The nonce is a 32-bit value that is determined by the miner such that the resulting signature of the block (when computed) starts with a certain number of 0s. The more 0s, the longer the search for the right nonce.  The function used to com- pute the signature of a block (called a hash function) is expensive to compute . To find the right nonce the miner must try many different nonces, which takes a lot of computation.  When a miner discovers the right nonce, it has “mined” a block.  The miner broadcasts the block to the rest of the peer-to-peer net- work, and if the block is verified and accepted by the majority of the peers, the miner collects a bitcoin. The transactions in the new block are removed from the mempool and the miner proceeds to the next block.  Note: the miner that mines the block first gets the reward.  All others restart on the next block.

The goal is to mine blocks as efficiently and as quickly as possible.  Mining takes computation, which re- quires computing hardware, electricity, cooling, and other supports that cost money.  Miners must be fast because only the first miner who successfully mines the block gets the reward.  Managing a computer in an efficient and fast manner is what good operating systems do. That is, designing a fast and efficient miner has similar challenges to designing a fast and efficient operating system.


The program will read in a sequence of four kinds of events (i)  mine a block (mine), (ii) receive a transaction and add it to the mempool (transaction), (iii) receive a block that was mined by another miner (block), and (iv) end the simulation (end).  For each of these events your program will need to perform a specific action as described below. These events correspond to actual events experienced by a real miner. For example, the transaction and block events correspond to the miner receiving transactions and blocks from the peer-to-peer network, and the mine event corresponds to the miner deciding to begin the cre- ation of a new block.

On a mine event:

1.    select transactions from its mempool in the order that the transactions were added

2.    create a new block from the selected transactions

3.    remove the selected transactions from the mempool

4.    print out the created block

On a transaction event:

1.    decode the transaction in the event

2.    add the transaction to the mempool

3.    print out the transaction

On a block event:

1.    decode the block. In the event

2.    remove any transactions in the mempool that were listed in the block

3.    print out the removed transactions in the order they were listed in the block

On an end event:

1.    exit
