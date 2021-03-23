import logging
import logging.config

"""Logging module

Usage example:

    from logger import log

    log.set_level_debug() # only needs to be set once per process.

    log.debug('print this message at log level DEBUG')
    log.info('print this message at log level INFO')
    log.warning('print this message at log level WARNING')
    log.error('print this message at log level ERROR')
    log.critical('print this message at log level CRITICAL')
"""

DEFAULT_LOGGING_LEVEL = logging.DEBUG
# LOG_FORMAT = '%(asctime)s %(process)d %(levelname)-8s %(module)s: %(message)s'
LOG_FORMAT = '{process:05d} {asctime} {levelname:8s} {filename}: {message}'

logger = logging.getLogger('zeromq-tut')
logger.setLevel(DEFAULT_LOGGING_LEVEL)
ch = logging.StreamHandler()
ch.setLevel(DEFAULT_LOGGING_LEVEL)
formatter = logging.Formatter(LOG_FORMAT, style='{')
ch.setFormatter(formatter)
logger.addHandler(ch)

def set_level_debug():
    logger.setLevel(logging.DEBUG)
    ch.setLevel(logging.DEBUG)
logger.set_level_debug = set_level_debug

def set_level_info():
    logger.setLevel(logging.INFO)
    ch.setLevel(logging.INFO)
logger.set_level_info = set_level_info

def set_level_warning():
    logger.setLevel(logging.WARNING)
    ch.setLevel(logging.WARNING)
logger.set_level_warning = set_level_warning

def set_level_error():
    logger.setLevel(logging.ERROR)
    ch.setLevel(logging.ERROR)
logger.set_level_error = set_level_error

def set_level_critical():
    logger.setLevel(logging.CRITICAL)
    ch.setLevel(logging.CRITICAL)
logger.set_level_critical = set_level_critical

log = logger
