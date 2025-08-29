import java.util.*;

class Pass2MacroProcessor {

    // Reuse the same MNTEntry structure as Pass1
    static class MNTEntry {
        String name;
        int mdtIndex;

        public MNTEntry(String name, int mdtIndex) {
            this.name = name;
            this.mdtIndex = mdtIndex;
        }
    }

    static class Pass2 {

        List<MNTEntry> MNT;     
        List<String> MDT;       
        List<String> intermediateCode; 

        public Pass2(List<MNTEntry> MNT, List<String> MDT, List<String> IC) {
            this.MNT = MNT;
            this.MDT = MDT;
            this.intermediateCode = IC;
        }

        public void expandCode() {
            System.out.println("Final Expanded Code:");
            for (String line : intermediateCode) {
                String[] parts = line.split("\\s+");
                String op = parts[0];

                // Check if line is a macro call
                MNTEntry macro = findMacro(op);
                if (macro != null) {
                    // Collect actual arguments
                    String[] args = Arrays.copyOfRange(parts, 1, parts.length);

                    // Expand macro using MDT
                    for (int i = macro.mdtIndex - 1; i < MDT.size(); i++) {
                        String mdtLine = MDT.get(i);
                        if (mdtLine.equals("MEND")) break;

                        String expanded = mdtLine;
                        for (int a = 0; a < args.length; a++) {
                            expanded = expanded.replace("#" + a, args[a]);
                        }
                        System.out.println(expanded);
                    }
                } else {
                    System.out.println(line);
                }
            }
        }

        private MNTEntry findMacro(String name) {
            for (MNTEntry entry : MNT) {
                if (entry.name.equals(name)) {
                    return entry;
                }
            }
            return null;
        }
    }

    public static void main(String[] args) {
        // From Pass1 output
        List<MNTEntry> MNT = new ArrayList<>();
        MNT.add(new MNTEntry("INCR", 1));

        List<String> MDT = new ArrayList<>();
        MDT.add("MOVER AREG,#0");
        MDT.add("ADD AREG,ONE");
        MDT.add("MOVEM AREG,#0");
        MDT.add("MEND");

        List<String> IC = Arrays.asList(
            "START 100",
            "READ ALPHA",
            "INCR ALPHA",
            "PRINT ALPHA",
            "END"
        );

        Pass2 pass2 = new Pass2(MNT, MDT, IC);
        pass2.expandCode();
    }
}

