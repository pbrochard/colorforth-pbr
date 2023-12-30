// The author disclaims copyright to this source code.

case OP_SEE: {
  POP1();
  cell entry_offset = p1;
  cell entry_index = find_entry_by_offset(&s->dict, entry_offset);
  see(s, entry_index);
  break;
}

case OP_DISASSEMBLE: {
  disassemble(s);
  break;
}

case OP_FULLROOM: {
  fullroom(s);
  break;
}

// case OP_ENTRY__PATCH: {
//   printf("ENTRY__PATCH");
//   break;
// }
//
// case OP_CHECK_DICT: {
//   printf("CHECK_DICT");
//   break;
// }
