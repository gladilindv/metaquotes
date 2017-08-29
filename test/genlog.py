#
# Created by null on 28.08.17.
#
import time
import logging
from random import randint
from multiprocessing.dummy import Pool as ThreadPool


FORMAT = "[%(asctime)-15s] [%(clientip)-15s] %(user)-8s [%(levelname)s] %(message)s"
logging.basicConfig(format=FORMAT, filename='example.log')

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)


usleep = lambda x: time.sleep(x/1000000.0)

errCodes = [
    'The price has changed. Retrying..',
    'No prices. Waiting for a new tick..',
    'Trading subsystem is busy. Retrying..',
    'Old version of the client terminal.',
    'Account is blocked.',
    'Trading is prohibited.'
]


def getIp():
    return ".".join(map(str, (randint(0, 255)
                             for _ in range(4))))

def getName():
    return "".join(map(str, (chr(65 + randint(0, 25))
                       for _ in range(6))))

def getAccount():
    n = 10
    range_start = 10**(n-1)
    range_end = (10**n)-1
    return randint(range_start, range_end)

def getTicket():
    n = 10
    range_start = 10**(n-1)
    range_end = (10**n)-1
    return randint(range_start, range_end)

class OrderManager:
    def __init__(self,amount):
        self.mAccount = getAccount()
        self.mIp = getIp()
        self.mName = getName()
        self.mAmount = amount

    def getBalance(self):
        b = randint(0, 10000) / 100.00
        b = self.mAmount
        d = {'clientip': self.mIp, 'user': self.mName}
        if b == 0:
            logger.critical('account %s balance is empty', self.mAccount, extra=d)
        else:
            logger.info('account %s balance is %.2f', self.mAccount, b, extra=d)

        return b

    def createOrder(self, amount):
        order = getTicket()
        d = {'clientip': self.mIp, 'user': self.mName}
        logger.info('order %s created', order, extra=d)
        self.mAmount -= amount
        return order

    def doTransction(self, order):
        ok = (order % 5 != 0)
        d = {'clientip': self.mIp, 'user': self.mName}
        if ok:
            logger.info('transaction success with account %s', self.mAccount, extra=d)
        else:
            logger.warning('transaction failed with account %s', self.mAccount, extra=d)
            error = randint(0, len(errCodes) - 1)
            logger.error(errCodes[error], extra=d)

        return ok

    def closeOrder(self, order):
        d = {'clientip': self.mIp, 'user': self.mName}
        logger.info('order %s closed', order, extra=d)

    def doIt(self):
        a = self.getBalance()
        while a > 0:
            percent = randint(0, 100) / 100
            ticket = self.createOrder(a * percent)
            self.doTransction(ticket)
            self.closeOrder(ticket)
            a = self.getBalance()


def moneySend(sum):
    mgr = OrderManager(sum)
    mgr.doIt()



if __name__ == '__main__':

    # make the Pool of workers
    pool = ThreadPool(4)

    # send some money for starting transactions
    # job the moneys in their own threads
    results = pool.map(moneySend, [c * 3 for c in range(10,70)])