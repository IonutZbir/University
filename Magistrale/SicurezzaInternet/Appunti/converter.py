import os
import subprocess
import sys

def convert_ppt_to_pdf_linux(ppt_path, pdf_path):
    libreoffice_path = '/usr/lib64/libreoffice/program/soffice'
    subprocess.run([libreoffice_path, '--headless', '--convert-to', 'pdf', ppt_path, '--outdir', os.path.dirname(pdf_path)])
    print(f'Converted {ppt_path} to {pdf_path}')
    
if __name__ == "__main__":
    dir_path = sys.argv[1] if len(sys.argv) > 1 else os.getcwd()
    out_dir = sys.argv[2] if len(sys.argv) > 2 else dir_path

    for root, _, files in os.walk(dir_path):
        for fname in files:
            if fname.lower().endswith(('.ppt', '.pptx')):
                ppt_path = os.path.join(root, fname)
                pdf_path = os.path.join(out_dir, os.path.splitext(fname)[0] + '.pdf')
                convert_ppt_to_pdf_linux(ppt_path, pdf_path)