
;; Function int testup_svcal() (_Z12testup_svcalv, funcdef_no=12, decl_uid=6903, cgraph_uid=12, symbol_order=12)

__attribute__((irqbox))
int testup_svcal() ()
{
  int * shouldNot;
  int b;
  int D.6913;

  b = 0;
  shouldNot = &b;
  *shouldNot = 10;
  D.6913 = 0;
  goto <D.6915>;
  <D.6915>:
  b = {CLOBBER};
  goto <D.6914>;
  <D.6914>:
  return D.6913;
}



;; Function int main() (main, funcdef_no=13, decl_uid=6908, cgraph_uid=13, symbol_order=13)

int main() ()
{
  int D.6916;

  D.6916 = 0;
  goto <D.6917>;
  D.6916 = 0;
  goto <D.6917>;
  <D.6917>:
  return D.6916;
}


