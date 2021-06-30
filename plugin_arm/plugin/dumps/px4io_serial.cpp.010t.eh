
;; Function uint8_t crc_packet(IOPacket*) (_ZL10crc_packetP8IOPacket, funcdef_no=248, decl_uid=11772, cgraph_uid=243, symbol_order=244)

__attribute__((unused))
uint8_t crc_packet(IOPacket*) (struct IOPacket * pkt)
{
  uint8_t c;
  uint8_t * p;
  uint8_t * end;
  uint8_t D.12635;
  int D.12634;
  unsigned char D.12633;
  unsigned char D.12632;
  uint8_t * p.0;
  int D.12628;
  int D.12627;
  unsigned char D.12626;

  D.12626 = pkt->count_code;
  D.12627 = (int) D.12626;
  D.12628 = D.12627 & 63;
  end = &pkt->regs[D.12628];
  p = pkt;
  c = 0;
  <D.12629>:
  if (p >= end) goto <D.11779>; else goto <D.12630>;
  <D.12630>:
  p.0 = p;
  p = p.0 + 1;
  D.12632 = *p.0;
  D.12633 = D.12632 ^ c;
  D.12634 = (int) D.12633;
  c = crc8_tab[D.12634];
  goto <D.12629>;
  <D.11779>:
  D.12635 = c;
  goto <D.12636>;
  <D.12636>:
  return D.12635;
}



;; Function device::Device* PX4IO_serial_interface() (_Z22PX4IO_serial_interfacev, funcdef_no=249, decl_uid=11781, cgraph_uid=244, symbol_order=247)

device::Device* PX4IO_serial_interface() ()
{
  void * D.11919;
  struct Device * D.12637;

  D.11919 = operator new (112);
  PX4IO_serial::PX4IO_serial (D.11919);
  D.12637 = D.11919;
  goto <D.12638>;
  <D.12638>:
  return D.12637;
}



;; Function void test_routine(unsigned int) (_Z12test_routinej, funcdef_no=250, decl_uid=11922, cgraph_uid=245, symbol_order=248)

__attribute__((irqbox))
void test_routine(unsigned int) (unsigned int status)
{
  int * p;
  int array[2];

  p = &array;
  *p = 10;
  array = {CLOBBER};
  return;
}



;; Function PX4IO_serial::PX4IO_serial() (_ZN12PX4IO_serialC2Ev, funcdef_no=252, decl_uid=11853, cgraph_uid=247, symbol_order=250)

PX4IO_serial::PX4IO_serial() (struct PX4IO_serial * const this)
{
  struct PX4IO_serial * D.12652;
  struct Device * D.12651;
  struct perf_ctr_header * D.12650;
  struct perf_ctr_header * D.12649;
  struct perf_ctr_header * D.12648;
  struct perf_ctr_header * D.12647;
  struct perf_ctr_header * D.12646;
  struct perf_ctr_header * D.12645;
  struct perf_ctr_header * D.12644;
  struct perf_ctr_header * D.12643;
  struct perf_ctr_header * D.12642;
  struct perf_ctr_header * D.12641;
  int (*__vtbl_ptr_type) () * D.12640;
  struct Device * D.12639;

  MEM[(struct  &)this] = {CLOBBER};
  D.12639 = &this->D.11864;
  device::Device::Device (D.12639, "PX4IO_serial", 0);
  D.12640 = &_ZTV12PX4IO_serial + 8;
  this->D.11864._vptr.Device = D.12640;
  this->_tx_dma = 0B;
  this->_rx_dma = 0B;
  this->_rx_dma_status = 2147483648;
  this->_bus_semaphore.semcount = 0;
  this->_bus_semaphore.holder.htcb = 0B;
  this->_bus_semaphore.holder.counts = 0;
  this->_completion_semaphore.semcount = 0;
  this->_completion_semaphore.holder.htcb = 0B;
  this->_completion_semaphore.holder.counts = 0;
  D.12641 = perf_alloc (1, "io_txns     ");
  this->_pc_txns = D.12641;
  D.12642 = perf_alloc (1, "io_dmasetup ");
  this->_pc_dmasetup = D.12642;
  D.12643 = perf_alloc (0, "io_retries  ");
  this->_pc_retries = D.12643;
  D.12644 = perf_alloc (0, "io_timeouts ");
  this->_pc_timeouts = D.12644;
  D.12645 = perf_alloc (0, "io_crcerrs  ");
  this->_pc_crcerrs = D.12645;
  D.12646 = perf_alloc (0, "io_dmaerrs  ");
  this->_pc_dmaerrs = D.12646;
  D.12647 = perf_alloc (0, "io_protoerrs");
  this->_pc_protoerrs = D.12647;
  D.12648 = perf_alloc (0, "io_uarterrs ");
  this->_pc_uerrs = D.12648;
  D.12649 = perf_alloc (0, "io_idle     ");
  this->_pc_idle = D.12649;
  D.12650 = perf_alloc (0, "io_badidle  ");
  this->_pc_badidle = D.12650;
  g_interface = this;
  <D.11986>:
  D.12652 = this;
  goto <D.12653>;
  <D.12653>:
  return D.12652;
}



;; Function PX4IO_serial::~PX4IO_serial() (_ZN12PX4IO_serialD2Ev, funcdef_no=255, decl_uid=11861, cgraph_uid=250, symbol_order=253)

PX4IO_serial::~PX4IO_serial() (struct PX4IO_serial * const this)
{
  void * D.12687;
  struct Device * D.12686;
  struct PX4IO_serial * g_interface.1;
  struct perf_ctr_header * D.12681;
  struct perf_ctr_header * D.12680;
  struct perf_ctr_header * D.12679;
  struct perf_ctr_header * D.12678;
  struct perf_ctr_header * D.12677;
  struct perf_ctr_header * D.12676;
  struct perf_ctr_header * D.12675;
  struct perf_ctr_header * D.12674;
  struct perf_ctr_header * D.12673;
  struct perf_ctr_header * D.12672;
  struct sem_t * D.12671;
  struct sem_t * D.12670;
  volatile uint32_t * D.12669;
  volatile uint32_t * D.12668;
  volatile uint32_t * D.12667;
  void * D.12665;
  void * D.12664;
  void * D.12661;
  void * D.12659;
  void * D.12658;
  void * D.12655;
  int (*__vtbl_ptr_type) () * D.12654;

  D.12654 = &_ZTV12PX4IO_serial + 8;
  this->D.11864._vptr.Device = D.12654;
  D.12655 = this->_tx_dma;
  if (D.12655 != 0B) goto <D.12656>; else goto <D.12657>;
  <D.12656>:
  D.12658 = this->_tx_dma;
  stm32_dmastop (D.12658);
  D.12659 = this->_tx_dma;
  stm32_dmafree (D.12659);
  goto <D.12660>;
  <D.12657>:
  <D.12660>:
  D.12661 = this->_rx_dma;
  if (D.12661 != 0B) goto <D.12662>; else goto <D.12663>;
  <D.12662>:
  D.12664 = this->_rx_dma;
  stm32_dmastop (D.12664);
  D.12665 = this->_rx_dma;
  stm32_dmafree (D.12665);
  goto <D.12666>;
  <D.12663>:
  <D.12666>:
  D.12667 = 1073812492B;
  *D.12667 = 0;
  D.12668 = 1073812496B;
  *D.12668 = 0;
  D.12669 = 1073812500B;
  *D.12669 = 0;
  up_disable_irq (87);
  irq_attach (87, 0B);
  stm32_unconfiggpio (625702);
  stm32_unconfiggpio (625703);
  D.12670 = &this->_completion_semaphore;
  sem_destroy (D.12670);
  D.12671 = &this->_bus_semaphore;
  sem_destroy (D.12671);
  D.12672 = this->_pc_txns;
  perf_free (D.12672);
  D.12673 = this->_pc_dmasetup;
  perf_free (D.12673);
  D.12674 = this->_pc_retries;
  perf_free (D.12674);
  D.12675 = this->_pc_timeouts;
  perf_free (D.12675);
  D.12676 = this->_pc_crcerrs;
  perf_free (D.12676);
  D.12677 = this->_pc_dmaerrs;
  perf_free (D.12677);
  D.12678 = this->_pc_protoerrs;
  perf_free (D.12678);
  D.12679 = this->_pc_uerrs;
  perf_free (D.12679);
  D.12680 = this->_pc_idle;
  perf_free (D.12680);
  D.12681 = this->_pc_badidle;
  perf_free (D.12681);
  g_interface.1 = g_interface;
  if (g_interface.1 == this) goto <D.12683>; else goto <D.12684>;
  <D.12683>:
  g_interface = 0B;
  goto <D.12685>;
  <D.12684>:
  <D.12685>:
  D.12686 = &this->D.11864;
  device::Device::~Device (D.12686);
  MEM[(struct  &)this] = {CLOBBER};
  <D.11996>:
  D.12687 = this;
  goto <D.12688>;
  <D.12688>:
  return D.12687;
}



;; Function virtual PX4IO_serial::~PX4IO_serial() (_ZN12PX4IO_serialD0Ev, funcdef_no=257, decl_uid=11855, cgraph_uid=252, symbol_order=255)

virtual PX4IO_serial::~PX4IO_serial() (struct PX4IO_serial * const this)
{
  void * D.12689;

  PX4IO_serial::~PX4IO_serial (this);
  <D.12000>:
  operator delete (this);
  D.12689 = this;
  goto <D.12690>;
  <D.12690>:
  return D.12689;
}



;; Function virtual int PX4IO_serial::init() (_ZN12PX4IO_serial4initEv, funcdef_no=258, decl_uid=11789, cgraph_uid=253, symbol_order=256)

virtual int PX4IO_serial::init() (struct PX4IO_serial * const this)
{
  uint32_t fraction;
  uint32_t mantissa;
  uint32_t usartdiv32;
  struct sem_t * D.12715;
  struct sem_t * D.12714;
  volatile uint32_t * D.12713;
  volatile uint32_t * D.12712;
  unsigned int D.12711;
  unsigned int D.12710;
  volatile uint32_t * D.12709;
  unsigned int D.12708;
  unsigned int D.12707;
  unsigned int D.12706;
  unsigned int vol.3;
  volatile uint32_t * D.12704;
  unsigned int vol.2;
  volatile uint32_t * D.12702;
  volatile uint32_t * D.12701;
  volatile uint32_t * D.12700;
  volatile uint32_t * D.12699;
  int D.12698;
  void * D.12697;
  void * D.12695;
  void * D.12692;
  void * D.12691;

  D.12691 = stm32_dmachannel (125);
  this->_tx_dma = D.12691;
  D.12692 = stm32_dmachannel (85);
  this->_rx_dma = D.12692;
  D.12695 = this->_tx_dma;
  if (D.12695 == 0B) goto <D.12693>; else goto <D.12696>;
  <D.12696>:
  D.12697 = this->_rx_dma;
  if (D.12697 == 0B) goto <D.12693>; else goto <D.12694>;
  <D.12693>:
  D.12698 = -1;
  goto <D.12716>;
  <D.12694>:
  stm32_configgpio (625702);
  stm32_configgpio (625703);
  D.12699 = 1073812492B;
  *D.12699 = 0;
  D.12700 = 1073812496B;
  *D.12700 = 0;
  D.12701 = 1073812500B;
  *D.12701 = 0;
  D.12702 = 1073812480B;
  vol.2 = *D.12702;
  D.12704 = 1073812484B;
  vol.3 = *D.12704;
  usartdiv32 = 112;
  mantissa = usartdiv32 >> 5;
  D.12706 = mantissa << 5;
  D.12707 = usartdiv32 - D.12706;
  D.12708 = D.12707 + 1;
  fraction = D.12708 >> 1;
  D.12709 = 1073812488B;
  D.12710 = mantissa << 4;
  D.12711 = D.12710 | fraction;
  *D.12709 = D.12711;
  irq_attach (87, _interrupt);
  up_enable_irq (87);
  D.12712 = 1073812500B;
  *D.12712 = 1;
  D.12713 = 1073812492B;
  *D.12713 = 8220;
  D.12714 = &this->_completion_semaphore;
  sem_init (D.12714, 0, 0);
  D.12715 = &this->_bus_semaphore;
  sem_init (D.12715, 0, 1);
  D.12698 = 0;
  goto <D.12716>;
  <D.12716>:
  return D.12698;
}



;; Function virtual int PX4IO_serial::ioctl(unsigned int, unsigned int&) (_ZN12PX4IO_serial5ioctlEjRj, funcdef_no=259, decl_uid=11803, cgraph_uid=254, symbol_order=257)

virtual int PX4IO_serial::ioctl(unsigned int, unsigned int&) (struct PX4IO_serial * const this, unsigned int operation, unsigned int & arg)
{
  uint16_t value;
  unsigned int count;
  unsigned int fails;
  struct perf_ctr_header * D.12754;
  struct perf_ctr_header * D.12753;
  struct perf_ctr_header * D.12752;
  struct perf_ctr_header * D.12751;
  struct perf_ctr_header * D.12750;
  struct perf_ctr_header * D.12749;
  struct perf_ctr_header * D.12748;
  struct perf_ctr_header * D.12747;
  struct perf_ctr_header * D.12746;
  struct perf_ctr_header * D.12745;
  int D.12739;
  int (*__vtbl_ptr_type) () D.12738;
  int (*__vtbl_ptr_type) () * D.12737;
  int (*__vtbl_ptr_type) () * D.12736;
  bool retval.6;
  short unsigned int value.5;
  int D.12732;
  volatile uint32_t * D.12731;
  unsigned int D.12729;
  unsigned int D.12728;
  volatile uint32_t * D.12727;
  bool retval.4;
  unsigned int D.12723;
  unsigned int D.12722;
  volatile uint32_t * D.12721;
  volatile uint32_t * D.12720;
  void * D.12719;
  void * D.12718;
  unsigned int D.12717;

  switch (operation) <default: <D.12019>, case 1: <D.12012>>
  <D.12012>:
  D.12717 = *arg;
  switch (D.12717) <default: <D.12756>, case 0: <D.12013>, case 1: <D.12014>, case 2: <D.12018>>
  <D.12013>:
  lowsyslog ("test 0\n");
  D.12718 = this->_tx_dma;
  stm32_dmastop (D.12718);
  D.12719 = this->_rx_dma;
  stm32_dmastop (D.12719);
  D.12720 = 1073812500B;
  D.12721 = 1073812500B;
  D.12722 = *D.12721;
  D.12723 = D.12722 & 4294967103;
  *D.12720 = D.12723;
  <D.12724>:
  <D.12725>:
  D.12727 = 1073812480B;
  D.12728 = *D.12727;
  D.12729 = D.12728 & 128;
  retval.4 = D.12729 == 0;
  if (retval.4 != 0) goto <D.12730>; else goto <D.12024>;
  <D.12730>:
  goto <D.12725>;
  <D.12024>:
  D.12731 = 1073812484B;
  *D.12731 = 85;
  goto <D.12724>;
  D.12732 = 0;
  goto <D.12757>;
  <D.12014>:
  fails = 0;
  count = 0;
  <D.12733>:
  value.5 = (short unsigned int) count;
  value = value.5;
  D.12736 = this->D.11864._vptr.Device;
  D.12737 = D.12736 + 20;
  D.12738 = *D.12737;
  D.12739 = OBJ_TYPE_REF(D.12738;(struct PX4IO_serial)this->5) (this, 32512, &value, 1);
  retval.6 = D.12739 != 0;
  if (retval.6 != 0) goto <D.12740>; else goto <D.12741>;
  <D.12740>:
  fails = fails + 1;
  goto <D.12742>;
  <D.12741>:
  <D.12742>:
  if (count > 4999) goto <D.12743>; else goto <D.12744>;
  <D.12743>:
  lowsyslog ("==== test 1 : %u failures ====\n", fails);
  D.12745 = this->_pc_txns;
  perf_print_counter (D.12745);
  D.12746 = this->_pc_dmasetup;
  perf_print_counter (D.12746);
  D.12747 = this->_pc_retries;
  perf_print_counter (D.12747);
  D.12748 = this->_pc_timeouts;
  perf_print_counter (D.12748);
  D.12749 = this->_pc_crcerrs;
  perf_print_counter (D.12749);
  D.12750 = this->_pc_dmaerrs;
  perf_print_counter (D.12750);
  D.12751 = this->_pc_protoerrs;
  perf_print_counter (D.12751);
  D.12752 = this->_pc_uerrs;
  perf_print_counter (D.12752);
  D.12753 = this->_pc_idle;
  perf_print_counter (D.12753);
  D.12754 = this->_pc_badidle;
  perf_print_counter (D.12754);
  count = 0;
  goto <D.12755>;
  <D.12744>:
  <D.12755>:
  value = {CLOBBER};
  count = count + 1;
  goto <D.12733>;
  D.12732 = 0;
  goto <D.12757>;
  <D.12018>:
  lowsyslog ("test 2\n");
  D.12732 = 0;
  goto <D.12757>;
  <D.12756>:
  <D.12019>:
  goto <D.12020>;
  <D.12020>:
  D.12732 = -1;
  goto <D.12757>;
  <D.12757>:
  return D.12732;
}



;; Function virtual int PX4IO_serial::write(unsigned int, void*, unsigned int) (_ZN12PX4IO_serial5writeEjPvj, funcdef_no=260, decl_uid=11799, cgraph_uid=255, symbol_order=258)

virtual int PX4IO_serial::write(unsigned int, void*, unsigned int) (struct PX4IO_serial * const this, unsigned int address, void * data, unsigned int count)
{
  unsigned int i;
  unsigned int retries;
  int result;
  const uint16_t * values;
  uint8_t offset;
  uint8_t page;
  struct sem_t * D.12780;
  struct perf_ctr_header * D.12779;
  struct perf_ctr_header * D.12777;
  int D.12774;
  int D.12773;
  unsigned char D.12772;
  unsigned int D.12767;
  unsigned char D.12766;
  unsigned char D.12765;
  struct sem_t * D.12762;
  int D.12761;
  unsigned int D.12758;

  D.12758 = address >> 8;
  page = (uint8_t) D.12758;
  offset = (uint8_t) address;
  values = data;
  if (count > 32) goto <D.12759>; else goto <D.12760>;
  <D.12759>:
  D.12761 = -22;
  goto <D.12784>;
  <D.12760>:
  D.12762 = &this->_bus_semaphore;
  sem_wait (D.12762);
  retries = 0;
  <D.12763>:
  if (retries > 2) goto <D.12040>; else goto <D.12764>;
  <D.12764>:
  D.12765 = (unsigned char) count;
  D.12766 = D.12765 | 64;
  _dma_buffer.count_code = D.12766;
  _dma_buffer.page = page;
  _dma_buffer.offset = offset;
  D.12767 = count * 2;
  memcpy (&_dma_buffer.regs[0], values, D.12767);
  i = count;
  <D.12768>:
  if (i > 31) goto <D.12042>; else goto <D.12769>;
  <D.12769>:
  _dma_buffer.regs[i] = 21930;
  i = i + 1;
  goto <D.12768>;
  <D.12042>:
  result = PX4IO_serial::_wait_complete (this);
  if (result == 0) goto <D.12770>; else goto <D.12771>;
  <D.12770>:
  D.12772 = _dma_buffer.count_code;
  D.12773 = (int) D.12772;
  D.12774 = D.12773 & 192;
  if (D.12774 == 128) goto <D.12775>; else goto <D.12776>;
  <D.12775>:
  result = -22;
  D.12777 = this->_pc_protoerrs;
  perf_count (D.12777);
  goto <D.12778>;
  <D.12776>:
  <D.12778>:
  goto <D.12040>;
  <D.12771>:
  D.12779 = this->_pc_retries;
  perf_count (D.12779);
  retries = retries + 1;
  goto <D.12763>;
  <D.12040>:
  D.12780 = &this->_bus_semaphore;
  sem_post (D.12780);
  if (result == 0) goto <D.12781>; else goto <D.12782>;
  <D.12781>:
  result = (int) count;
  goto <D.12783>;
  <D.12782>:
  <D.12783>:
  D.12761 = result;
  goto <D.12784>;
  <D.12784>:
  return D.12761;
}



;; Function virtual int PX4IO_serial::read(unsigned int, void*, unsigned int) (_ZN12PX4IO_serial4readEjPvj, funcdef_no=261, decl_uid=11794, cgraph_uid=256, symbol_order=259)

virtual int PX4IO_serial::read(unsigned int, void*, unsigned int) (struct PX4IO_serial * const this, unsigned int address, void * data, unsigned int count)
{
  unsigned int retries;
  int result;
  uint16_t * values;
  uint8_t offset;
  uint8_t page;
  struct sem_t * D.12811;
  struct perf_ctr_header * D.12810;
  unsigned int D.12809;
  struct perf_ctr_header * D.12807;
  unsigned int D.12804;
  unsigned int D.12803;
  unsigned char D.12802;
  struct perf_ctr_header * D.12800;
  int D.12797;
  int D.12796;
  unsigned char D.12795;
  unsigned char D.12792;
  struct sem_t * D.12789;
  int D.12788;
  unsigned int D.12785;

  D.12785 = address >> 8;
  page = (uint8_t) D.12785;
  offset = (uint8_t) address;
  values = data;
  if (count > 32) goto <D.12786>; else goto <D.12787>;
  <D.12786>:
  D.12788 = -22;
  goto <D.12815>;
  <D.12787>:
  D.12789 = &this->_bus_semaphore;
  sem_wait (D.12789);
  retries = 0;
  <D.12790>:
  if (retries > 2) goto <D.12055>; else goto <D.12791>;
  <D.12791>:
  D.12792 = (unsigned char) count;
  _dma_buffer.count_code = D.12792;
  _dma_buffer.page = page;
  _dma_buffer.offset = offset;
  result = PX4IO_serial::_wait_complete (this);
  if (result == 0) goto <D.12793>; else goto <D.12794>;
  <D.12793>:
  D.12795 = _dma_buffer.count_code;
  D.12796 = (int) D.12795;
  D.12797 = D.12796 & 192;
  if (D.12797 == 128) goto <D.12798>; else goto <D.12799>;
  <D.12798>:
  result = -22;
  D.12800 = this->_pc_protoerrs;
  perf_count (D.12800);
  goto <D.12801>;
  <D.12799>:
  D.12802 = _dma_buffer.count_code;
  D.12803 = (unsigned int) D.12802;
  D.12804 = D.12803 & 63;
  if (D.12804 != count) goto <D.12805>; else goto <D.12806>;
  <D.12805>:
  result = -5;
  D.12807 = this->_pc_protoerrs;
  perf_count (D.12807);
  goto <D.12808>;
  <D.12806>:
  D.12809 = count * 2;
  memcpy (values, &_dma_buffer.regs[0], D.12809);
  <D.12808>:
  <D.12801>:
  goto <D.12055>;
  <D.12794>:
  D.12810 = this->_pc_retries;
  perf_count (D.12810);
  retries = retries + 1;
  goto <D.12790>;
  <D.12055>:
  D.12811 = &this->_bus_semaphore;
  sem_post (D.12811);
  if (result == 0) goto <D.12812>; else goto <D.12813>;
  <D.12812>:
  result = (int) count;
  goto <D.12814>;
  <D.12813>:
  <D.12814>:
  D.12788 = result;
  goto <D.12815>;
  <D.12815>:
  return D.12788;
}



;; Function int PX4IO_serial::_wait_complete() (_ZN12PX4IO_serial14_wait_completeEv, funcdef_no=262, decl_uid=11813, cgraph_uid=257, symbol_order=260)

int PX4IO_serial::_wait_complete() (struct PX4IO_serial * const this)
{
  uint8_t crc;
  int ret;
  struct timespec abstime;
  int D.12886;
  struct perf_ctr_header * D.12885;
  int D.12884;
  int * D.12883;
  struct perf_ctr_header * D.12882;
  struct perf_ctr_header * D.12881;
  int D.12878;
  int * D.12877;
  bool retval.14;
  struct perf_ctr_header * D.12875;
  bool D.12872;
  int D.12871;
  int D.12870;
  unsigned char D.12869;
  bool D.12868;
  unsigned char D.12867;
  bool retval.13;
  struct perf_ctr_header * D.12865;
  unsigned int D.12862;
  unsigned int D.12861;
  bool retval.12;
  struct sem_t * D.12857;
  long int D.12854;
  long int D.12853;
  unsigned int D.12852;
  unsigned int D.12851;
  long int D.12848;
  long int D.12847;
  long int D.12846;
  struct perf_ctr_header * D.12845;
  unsigned int D.12844;
  unsigned int D.12843;
  volatile uint32_t * D.12842;
  volatile uint32_t * D.12841;
  void * D.12840;
  unsigned int D.12839;
  int D.12838;
  int _dma_buffer.11;
  int D.12836;
  uint16_t * D.12835;
  int D.12834;
  int D.12833;
  unsigned char D.12832;
  unsigned int _dma_buffer.10;
  void * D.12830;
  unsigned char D.12829;
  unsigned int D.12828;
  unsigned int D.12827;
  volatile uint32_t * D.12826;
  volatile uint32_t * D.12825;
  void * D.12824;
  unsigned int _dma_buffer.9;
  void * D.12822;
  struct perf_ctr_header * D.12821;
  struct perf_ctr_header * D.12820;
  unsigned int vol.8;
  volatile uint32_t * D.12818;
  unsigned int vol.7;
  volatile uint32_t * D.12816;

  D.12816 = 1073812480B;
  vol.7 = *D.12816;
  D.12818 = 1073812484B;
  vol.8 = *D.12818;
  D.12820 = this->_pc_txns;
  perf_begin (D.12820);
  D.12821 = this->_pc_dmasetup;
  perf_begin (D.12821);
  this->_rx_dma_status = 0;
  D.12822 = this->_rx_dma;
  _dma_buffer.9 = (unsigned int) &_dma_buffer;
  stm32_dmasetup (D.12822, 1073812484, _dma_buffer.9, 68, 1280);
  D.12824 = this->_rx_dma;
  stm32_dmastart (D.12824, _dma_callback, this, 0);
  D.12825 = 1073812500B;
  D.12826 = 1073812500B;
  D.12827 = *D.12826;
  D.12828 = D.12827 | 64;
  *D.12825 = D.12828;
  _dma_buffer.crc = 0;
  D.12829 = crc_packet (&_dma_buffer);
  _dma_buffer.crc = D.12829;
  D.12830 = this->_tx_dma;
  _dma_buffer.10 = (unsigned int) &_dma_buffer;
  D.12832 = _dma_buffer.count_code;
  D.12833 = (int) D.12832;
  D.12834 = D.12833 & 63;
  D.12835 = &_dma_buffer.regs[D.12834];
  D.12836 = (int) D.12835;
  _dma_buffer.11 = (int) &_dma_buffer;
  D.12838 = D.12836 - _dma_buffer.11;
  D.12839 = (unsigned int) D.12838;
  stm32_dmasetup (D.12830, 1073812484, _dma_buffer.10, D.12839, 1088);
  D.12840 = this->_tx_dma;
  stm32_dmastart (D.12840, 0B, 0B, 0);
  D.12841 = 1073812500B;
  D.12842 = 1073812500B;
  D.12843 = *D.12842;
  D.12844 = D.12843 | 128;
  *D.12841 = D.12844;
  D.12845 = this->_pc_dmasetup;
  perf_end (D.12845);
  clock_gettime (0, &abstime);
  D.12846 = abstime.tv_nsec;
  D.12847 = D.12846 + 10000000;
  abstime.tv_nsec = D.12847;
  D.12848 = abstime.tv_nsec;
  if (D.12848 > 999999999) goto <D.12849>; else goto <D.12850>;
  <D.12849>:
  D.12851 = abstime.tv_sec;
  D.12852 = D.12851 + 1;
  abstime.tv_sec = D.12852;
  D.12853 = abstime.tv_nsec;
  D.12854 = D.12853 + -1000000000;
  abstime.tv_nsec = D.12854;
  goto <D.12855>;
  <D.12850>:
  <D.12855>:
  <D.12856>:
  D.12857 = &this->_completion_semaphore;
  ret = sem_timedwait (D.12857, &abstime);
  if (ret == 0) goto <D.12858>; else goto <D.12859>;
  <D.12858>:
  D.12861 = this->_rx_dma_status;
  D.12862 = D.12861 & 8;
  retval.12 = D.12862 != 0;
  if (retval.12 != 0) goto <D.12863>; else goto <D.12864>;
  <D.12863>:
  D.12865 = this->_pc_dmaerrs;
  perf_count (D.12865);
  ret = -5;
  goto <D.12096>;
  <D.12864>:
  crc = _dma_buffer.crc;
  _dma_buffer.crc = 0;
  D.12867 = crc_packet (&_dma_buffer);
  D.12868 = D.12867 != crc;
  D.12869 = _dma_buffer.count_code;
  D.12870 = (int) D.12869;
  D.12871 = D.12870 & 192;
  D.12872 = D.12871 == 64;
  retval.13 = D.12868 | D.12872;
  if (retval.13 != 0) goto <D.12873>; else goto <D.12874>;
  <D.12873>:
  D.12875 = this->_pc_crcerrs;
  perf_count (D.12875);
  ret = -5;
  goto <D.12096>;
  <D.12874>:
  goto <D.12096>;
  <D.12859>:
  D.12877 = get_errno_ptr ();
  D.12878 = *D.12877;
  retval.14 = D.12878 == 110;
  if (retval.14 != 0) goto <D.12879>; else goto <D.12880>;
  <D.12879>:
  PX4IO_serial::_abort_dma (this);
  D.12881 = this->_pc_timeouts;
  perf_count (D.12881);
  D.12882 = this->_pc_txns;
  perf_cancel (D.12882);
  goto <D.12096>;
  <D.12880>:
  D.12883 = get_errno_ptr ();
  D.12884 = *D.12883;
  lowsyslog ("unexpected ret %d/%d\n", ret, D.12884);
  goto <D.12856>;
  <D.12096>:
  this->_rx_dma_status = 2147483648;
  D.12885 = this->_pc_txns;
  perf_end (D.12885);
  D.12886 = ret;
  goto <D.12888>;
  <D.12888>:
  abstime = {CLOBBER};
  goto <D.12887>;
  <D.12887>:
  return D.12886;
}



;; Function static void PX4IO_serial::_dma_callback(DMA_HANDLE, uint8_t, void*) (_ZN12PX4IO_serial13_dma_callbackEPvhS0_, funcdef_no=263, decl_uid=11818, cgraph_uid=258, symbol_order=261)

static void PX4IO_serial::_dma_callback(DMA_HANDLE, uint8_t, void*) (void * handle, uint8_t status, void * arg)
{
  struct PX4IO_serial * ps;
  unsigned int D.12891;

  if (arg != 0B) goto <D.12889>; else goto <D.12890>;
  <D.12889>:
  ps = arg;
  D.12891 = (unsigned int) status;
  PX4IO_serial::_do_rx_dma_callback (ps, D.12891);
  goto <D.12892>;
  <D.12890>:
  <D.12892>:
  return;
}



;; Function void PX4IO_serial::_do_rx_dma_callback(unsigned int) (_ZN12PX4IO_serial19_do_rx_dma_callbackEj, funcdef_no=264, decl_uid=11820, cgraph_uid=259, symbol_order=262)

__attribute__((irqbox))
void PX4IO_serial::_do_rx_dma_callback(unsigned int) (struct PX4IO_serial * const this, unsigned int status)
{
  uint32_t sr;
  struct sem_t * D.12908;
  unsigned int D.12907;
  unsigned int D.12906;
  volatile uint32_t * D.12905;
  volatile uint32_t * D.12904;
  unsigned int vol.16;
  volatile uint32_t * D.12901;
  unsigned int D.12898;
  volatile uint32_t * D.12897;
  unsigned int D.12894;
  bool retval.15;

  D.12894 = this->_rx_dma_status;
  retval.15 = D.12894 == 0;
  if (retval.15 != 0) goto <D.12895>; else goto <D.12896>;
  <D.12895>:
  D.12897 = 1073812480B;
  sr = *D.12897;
  D.12898 = sr & 40;
  if (D.12898 != 0) goto <D.12899>; else goto <D.12900>;
  <D.12899>:
  D.12901 = 1073812484B;
  vol.16 = *D.12901;
  status = 8;
  goto <D.12903>;
  <D.12900>:
  <D.12903>:
  this->_rx_dma_status = status;
  D.12904 = 1073812500B;
  D.12905 = 1073812500B;
  D.12906 = *D.12905;
  D.12907 = D.12906 & 4294967103;
  *D.12904 = D.12907;
  D.12908 = &this->_completion_semaphore;
  sem_post (D.12908);
  goto <D.12909>;
  <D.12896>:
  <D.12909>:
  test_routine (status);
  return;
}



;; Function static int PX4IO_serial::_interrupt(int, void*) (_ZN12PX4IO_serial10_interruptEiPv, funcdef_no=265, decl_uid=11824, cgraph_uid=260, symbol_order=263)

static int PX4IO_serial::_interrupt(int, void*) (int irq, void * context)
{
  int D.12915;
  struct PX4IO_serial * g_interface.18;
  struct PX4IO_serial * g_interface.17;

  g_interface.17 = g_interface;
  if (g_interface.17 != 0B) goto <D.12911>; else goto <D.12912>;
  <D.12911>:
  g_interface.18 = g_interface;
  PX4IO_serial::_do_interrupt (g_interface.18);
  goto <D.12914>;
  <D.12912>:
  <D.12914>:
  D.12915 = 0;
  goto <D.12916>;
  <D.12916>:
  return D.12915;
}



;; Function void PX4IO_serial::_do_interrupt() (_ZN12PX4IO_serial13_do_interruptEv, funcdef_no=266, decl_uid=11825, cgraph_uid=261, symbol_order=264)

void PX4IO_serial::_do_interrupt() (struct PX4IO_serial * const this)
{
  size_t length;
  uint32_t sr;
  void * D.12951;
  struct perf_ctr_header * D.12950;
  void * D.12949;
  struct perf_ctr_header * D.12948;
  unsigned int D.12947;
  int D.12946;
  int _dma_buffer.22;
  int D.12944;
  uint16_t * D.12943;
  int D.12942;
  int D.12941;
  unsigned char D.12940;
  unsigned int D.12936;
  void * D.12935;
  unsigned int D.12932;
  bool retval.21;
  unsigned int D.12928;
  struct perf_ctr_header * D.12927;
  unsigned int D.12924;
  bool retval.20;
  unsigned int D.12920;
  unsigned int vol.19;
  volatile uint32_t * D.12918;
  volatile uint32_t * D.12917;

  D.12917 = 1073812480B;
  sr = *D.12917;
  D.12918 = 1073812484B;
  vol.19 = *D.12918;
  D.12920 = sr & 14;
  if (D.12920 != 0) goto <D.12921>; else goto <D.12922>;
  <D.12921>:
  D.12924 = this->_rx_dma_status;
  retval.20 = D.12924 == 0;
  if (retval.20 != 0) goto <D.12925>; else goto <D.12926>;
  <D.12925>:
  PX4IO_serial::_abort_dma (this);
  D.12927 = this->_pc_uerrs;
  perf_count (D.12927);
  PX4IO_serial::_do_rx_dma_callback (this, 8);
  goto <D.12954>;
  <D.12926>:
  goto <D.12954>;
  <D.12922>:
  D.12928 = sr & 16;
  if (D.12928 != 0) goto <D.12929>; else goto <D.12930>;
  <D.12929>:
  D.12932 = this->_rx_dma_status;
  retval.21 = D.12932 == 0;
  if (retval.21 != 0) goto <D.12933>; else goto <D.12934>;
  <D.12933>:
  D.12935 = this->_rx_dma;
  D.12936 = stm32_dmaresidual (D.12935);
  length = 68 - D.12936;
  if (length == 0) goto <D.12937>; else goto <D.12939>;
  <D.12939>:
  D.12940 = _dma_buffer.count_code;
  D.12941 = (int) D.12940;
  D.12942 = D.12941 & 63;
  D.12943 = &_dma_buffer.regs[D.12942];
  D.12944 = (int) D.12943;
  _dma_buffer.22 = (int) &_dma_buffer;
  D.12946 = D.12944 - _dma_buffer.22;
  D.12947 = (unsigned int) D.12946;
  if (D.12947 > length) goto <D.12937>; else goto <D.12938>;
  <D.12937>:
  D.12948 = this->_pc_badidle;
  perf_count (D.12948);
  D.12949 = this->_rx_dma;
  stm32_dmastop (D.12949);
  PX4IO_serial::_do_rx_dma_callback (this, 8);
  goto <D.12954>;
  <D.12938>:
  D.12950 = this->_pc_idle;
  perf_count (D.12950);
  D.12951 = this->_rx_dma;
  stm32_dmastop (D.12951);
  PX4IO_serial::_do_rx_dma_callback (this, 32);
  goto <D.12952>;
  <D.12934>:
  <D.12952>:
  goto <D.12953>;
  <D.12930>:
  <D.12953>:
  <D.12954>:
  return;
}



;; Function void PX4IO_serial::_abort_dma() (_ZN12PX4IO_serial10_abort_dmaEv, funcdef_no=267, decl_uid=11827, cgraph_uid=262, symbol_order=265)

void PX4IO_serial::_abort_dma() (struct PX4IO_serial * const this)
{
  void * D.12966;
  void * D.12965;
  unsigned int vol.25;
  volatile uint32_t * D.12963;
  unsigned int vol.24;
  volatile uint32_t * D.12961;
  unsigned int vol.23;
  volatile uint32_t * D.12959;
  unsigned int D.12958;
  unsigned int D.12957;
  volatile uint32_t * D.12956;
  volatile uint32_t * D.12955;

  D.12955 = 1073812500B;
  D.12956 = 1073812500B;
  D.12957 = *D.12956;
  D.12958 = D.12957 & 4294967103;
  *D.12955 = D.12958;
  D.12959 = 1073812480B;
  vol.23 = *D.12959;
  D.12961 = 1073812484B;
  vol.24 = *D.12961;
  D.12963 = 1073812484B;
  vol.25 = *D.12963;
  D.12965 = this->_tx_dma;
  stm32_dmastop (D.12965);
  D.12966 = this->_rx_dma;
  stm32_dmastop (D.12966);
  return;
}


